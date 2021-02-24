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
brdc24File = 'output24h.txt';
brdcbestFile = 'outputbest.txt';

almanacFile = 'Almanac-SatPos-PRN12.txt';
PredFile = 'igu21394_00.sp3';
ObsFile = 'igu21395_00.sp3';
%rapidFile = 'igrwwwwd.sp3';

truepos = load("true pos.txt");

%% Read Files
refsat=readSP3(preciseFile);   %%Read the sp3 file
%% Sky plot of satellkite
   %calculate the vector from receiver to satellites in xyz
   xyz_kr = [refsat(:,4)*1000-truepos(1,1), refsat(:,5)*1000-truepos(1,2), refsat(:,6)*1000-truepos(1,3)];
   
   %transform the vector to ENU
   %assume sphere, all in radians
   lat = asin(truepos(1,3)/(sqrt(truepos(1,1)^2+truepos(1,2)^2+truepos(1,3)^2)));
   lon = asin(truepos(1,2)/(sqrt(truepos(1,1)^2+truepos(1,2)^2+truepos(1,3)^2)))/cos(lat);
   R = [-sin(lon), cos(lon), 0; -sin(lat)*cos(lon), -sin(lat)*sin(lon), cos(lat); cos(lat)*cos(lon), cos(lat)*sin(lon), sin(lat)];
   
   enu = zeros(size(xyz_kr, 1), size(xyz_kr,2));
   for i = 1:size(xyz_kr, 1)
       enu(i,1:3) = transpose(R*transpose(xyz_kr(i,1:3)));
   end 
   
   %calculate the azimuth and elevation
   ele = asind(enu(:,3)./sqrt(enu(:,1).^2+enu(:,2).^2+enu(:,3).^2));
   azi = atan2d(enu(:,1), enu(:,2));
   
   %plot the sky plot
   ind = [];
   for i = 1:size(ele,1)
       if ele(i,1) < 0
           ind = [ind, i];
       end 
   end
   ele(ind,:) = [];
   azi(ind,:) = [];

   skyp = skyplot(azi,ele,'.','b');
   
   %calculate the DOP
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
       end
   end 
%% Parse out PRN 11
idx=find(refsat(:,1)==prn);
PRN11=refsat(idx,:);
%% Plots

%% Statistics
