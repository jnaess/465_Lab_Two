% File Name:        main.m
% -------------------------------------------------------------------------
% 
% Purpose of file:  Contains the main function
%
% -------------------------------------------------------------------------
%
% Remarks:          You will need to write your own functions to...
%                   1)  Read the satellite coordinates that you generate
%						from the broadcast ephemeris
%					2) 	Read the igs ephemeris files using the readSP3()
%						function
%					3) 	Generate sky plot of satellites based on the
%					    satellite  and the pillar coordiantes
%                   4)  Calculte the error of different kinds of ephemeris
%                       with precise orbits (igswwwwd.sp3) as reference

%  You can modify any part of this code to make it more convenient for you
%  to use. This just provides a general procedure.
%-------------------------------------------------------------------------%


% Main function...

% clear memory, figures, command window, output numbers in standard notation
clear all;
close all;
clc;
format long g;

%% User Inputs
prn = 11;

preciseFile = 'igs21394.sp3';
%brdc24File = 'output24h.txt';
%brdcbestFile = 'outputbest.txt';

almanacFile = 'Almanac-SatPos-PRN12.txt';
PredFile = 'igu21394_00.sp3';
ObsFile = 'igu21395_00.sp3';
%rapidFile = 'igrwwwwd.sp3';

truepos = load("true pos.txt");

%% Read Files
refsat=readSP3(preciseFile);   %%Read the sp3 file
%% Sky plot of satellite
%    %calculate the vector from receiver to satellites in xyz
   xyz_kr = [refsat(:,4)*1000-truepos(1,1), refsat(:,5)*1000-truepos(1,2), refsat(:,6)*1000-truepos(1,3)];
%    
%    %transform the vector to ENU
%    %assume sphere, all in radians
   lat = asin(truepos(1,3)/(sqrt(truepos(1,1)^2+truepos(1,2)^2+truepos(1,3)^2)));
   lon = asin(truepos(1,2)/(sqrt(truepos(1,1)^2+truepos(1,2)^2+truepos(1,3)^2)))/cos(lat);
   R = [-sin(lon), cos(lon), 0; -sin(lat)*cos(lon), -sin(lat)*sin(lon), cos(lat); cos(lat)*cos(lon), cos(lat)*sin(lon), sin(lat)];
%    
   enu = zeros(size(xyz_kr, 1), size(xyz_kr,2));
   for i = 1:size(xyz_kr, 1)
       enu(i,1:3) = transpose(R*transpose(xyz_kr(i,1:3)));
   end 
   
   %calculate the azimuth and elevation
   ele = asind(enu(:,3)./sqrt(enu(:,1).^2+enu(:,2).^2+enu(:,3).^2));
   azi = atan2d(enu(:,1), enu(:,2));
   ele = [ele, refsat(:,1)];
   
   %plot the sky plot
   %find indices of non-visible satellites
   ind = [];
   for i = 1:size(ele,1)
       if ele(i,1) < 0
           ind = [ind, i];
       end 
   end

   %rearrange for skyplot
   for prn = 1:32
       ele_curr = [];
       azi_curr = [];
     for ep = 1:size(ele, 1)
         if ele(ep, 2) == prn
            if ele(ep,1) < 0
                ele_curr = [ele_curr; NaN];
                azi_curr = [azi_curr; NaN];
            else
                ele_curr = [ele_curr; ele(ep,1)];
                azi_curr = [azi_curr; azi(ep,1)];
            end
         end
     end 
        skyp = skyplot(azi_curr,ele_curr,'-');
        hold on;
   end 
   
 %% calculate the DOP
   vis_sat = refsat;
   vis_sat(ind,:) = [];
   vis_sat(:, 4:6) = vis_sat(:, 4:6)*1000;
   
   A = [];
   DOP = [];
   sat = 0;
   for i = 1:size(vis_sat,1)-1
       p = sqrt((truepos(1,1)-vis_sat(i,4)).^2+(truepos(1,2)-vis_sat(i,5)).^2+(truepos(1,3)-vis_sat(i,6)).^2);
       Ax = (truepos(1,1)-vis_sat(i,4))/p;
       Ay = (truepos(1,2)-vis_sat(i,5))/p;
       Az = (truepos(1,3)-vis_sat(i,6))/p;
       A = [A; Ax Ay Az -1];
       sat = sat + 1;
       if vis_sat(i+1,3) ~= vis_sat(i,3)
           Q = inv(transpose(A)*A);
           Q = R*Q(1:3, 1:3)*transpose(R);
           DOP = [DOP; vis_sat(i,3), sat, sqrt(Q(1,1)), sqrt(Q(2,2)), sqrt(Q(1,1)+Q(2,2)), sqrt(Q(3,3))]; 
           
           A = [];
           sat = 0;
       elseif i == size(vis_sat,1)-1
           Q = inv(transpose(A)*A);
           Q = R*Q(1:3, 1:3)*transpose(R);
           DOP = [DOP; vis_sat(i,3), sat, sqrt(Q(1,1)), sqrt(Q(2,2)), sqrt(Q(1,1)+Q(2,2)), sqrt(Q(3,3))]; 
       end
   end 
   figure()
    hold on;
    grid on;
    yyaxis left;
    plot(DOP(:,1), DOP(:,3), '-b');
    plot(DOP(:,1), DOP(:,4), '-g');
    plot(DOP(:,1), DOP(:,5), '-r');
    ylabel("DOP");
    ylim([0, 4]);
    plot(DOP(:,1), DOP(:,6), '-m');
    yyaxis right;
    plot(DOP(:,1), DOP(:,2), '-k');
    legend('EDOP', 'NDOP', 'HDOP', 'VDOP', 'Number of Satellites');
    title("Dilution of Precision");
    xlabel("Ephemeries (Seconds of Week)");
    ylim([0, 22]);
    ylabel("Number of visible satellites");
    print(gcf, "DOPs.png", '-dpng', '-r300');
    hold off;
%% Parse out PRN 11
idx=find(refsat(:,1)==prn);
PRN11=refsat(idx,:);

%% Task 3
brdcbest = load("brdcbest.xyz");
brdc24hr = load ("brdc24hr.xyz");

sat12 = load(almanacFile);

pred = readSP3(PredFile);
obs = readSP3(ObsFile);

%precise file = refsat

%3.5 orbital position error x5
refsat12 = [];
pred12 = [];
obs12 = [];
for i = 1:size(refsat, 1)
    if refsat(i,1) == 12
        refsat12 = [refsat12; refsat(i,4:6)*1000];
    end 
end

for j = 1:size(brdcbest, 1)
    for i = 1:size(pred, 1)
        if pred(i,1) == 12 && pred(i,3) == brdcbest(j,1)
            pred12 = [pred12; pred(i, 4:6)*1000];
        end
    end
    for i = 1:size(pred, 1)
        if obs(i,1) == 12 && obs(i,3) == brdcbest(j,1)
            obs12 = [obs12; obs(i, 4:6)*1000];
        end 
    end
end

err_brdcbest = [brdcbest(:,2)-refsat12(:,1), brdcbest(:,3)-refsat12(:,2), brdcbest(:,4)-refsat12(:,3)];
err_brdc24hr = [brdc24hr(:,2)-refsat12(:,1), brdc24hr(:,3)-refsat12(:,2), brdc24hr(:,4)-refsat12(:,3)];
err_pred = [pred12(:,1)-refsat12(:,1), pred12(:,2)-refsat12(:,2), pred12(:,3)-refsat12(:,3)];
err_obs = [obs12(:,1)-refsat12(:,1), obs12(:,2)-refsat12(:,2), obs12(:,3)-refsat12(:,3)];
err_almanac = [sat12(:,2)-refsat12(:,1), sat12(:,3)-refsat12(:,2), sat12(:,4)-refsat12(:,3)];

%3.6 plots
ephem = sat12(:,1);

figure();
plot(ephem(:,1), err_brdcbest(:,1), '-b');
hold on;
grid on;
plot(ephem(:,1), err_brdcbest(:,2), '-g');
plot(ephem(:,1), err_brdcbest(:,3), '-r');
%plot(ephem(:,1), sqrt(err_brdcbest(:,1).^2+err_brdcbest(:,2).^2+err_brdcbest(:,3).^2), '-k');
legend('x', 'y', 'z');
title("Errors in Best Broadcast File");
xlabel("Ephemeries (Seconds of Week)");
ylabel("Error (m)");
ylim([-4, 4]);
print(gcf, "brdcbest_errors.png", '-dpng', '-r300');
hold off;

figure();
plot(ephem(:,1), err_brdc24hr(:,1), '-b');
hold on;
grid on;
plot(ephem(:,1), err_brdc24hr(:,2), '-g');
plot(ephem(:,1), err_brdc24hr(:,3), '-r');
%plot(ephem(:,1), sqrt(err_brdcbest(:,1).^2+err_brdcbest(:,2).^2+err_brdcbest(:,3).^2), '-k');
legend('x', 'y', 'z');
title("Errors in 24hr Broadcast File");
xlabel("Ephemeries (Seconds of Week)");
ylabel("Error (m)");
ylim([-1200, 1200]);
print(gcf, "brdc24hr_errors.png", '-dpng', '-r300');
hold off;

figure();
plot(ephem(:,1), err_almanac(:,1), '-b');
hold on;
grid on;
plot(ephem(:,1), err_almanac(:,2), '-g');
plot(ephem(:,1), err_almanac(:,3), '-r');
%plot(ephem(:,1), sqrt(err_brdcbest(:,1).^2+err_brdcbest(:,2).^2+err_brdcbest(:,3).^2), '-k');
legend('x', 'y', 'z');
title("Errors in Almanac File");
xlabel("Ephemeries (Seconds of Week)");
ylabel("Error (m)");
ylim([-4000, 4000]);
print(gcf, "almanac_errors.png", '-dpng', '-r300');
hold off;

figure();
plot(ephem(:,1), err_obs(:,1), '-b');
hold on;
grid on;
plot(ephem(:,1), err_obs(:,2), '-g');
plot(ephem(:,1), err_obs(:,3), '-r');
%plot(ephem(:,1), sqrt(err_brdcbest(:,1).^2+err_brdcbest(:,2).^2+err_brdcbest(:,3).^2), '-k');
legend('x', 'y', 'z');
title("Errors in Observation File");
xlabel("Ephemeries (Seconds of Week)");
ylabel("Error (m)");
ylim([-1, 1]);
print(gcf, "obs_errors.png", '-dpng', '-r300');
hold off;

figure();
plot(ephem(:,1), err_pred(:,1), '-b');
hold on;
grid on;
plot(ephem(:,1), err_pred(:,2), '-g');
plot(ephem(:,1), err_pred(:,3), '-r');
%plot(ephem(:,1), sqrt(err_brdcbest(:,1).^2+err_brdcbest(:,2).^2+err_brdcbest(:,3).^2), '-k');
legend('x', 'y', 'z');
title("Errors in Predicted File");
xlabel("Ephemeries (Seconds of Week)");
ylabel("Error (m)");
ylim([-1, 1]);
print(gcf, "pred_errors.png", '-dpng', '-r300');
hold off;






