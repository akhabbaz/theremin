function [ticks] = timeInTicks(time, divisor, maxcounts)
%  time is time in seconds
% divisor is one of 1, 8, 64, 256, 1024
% maxcount is 256 or 65536
%
% ticks are overflows and ticks
if nargin < 3
    maxcounts = 256;
end
clck = 16000000;
Tclck = 1/clck;

Tclck = divisor * Tclck;
totalTicks = time/Tclck -1;
overflows = floor(totalTicks/maxcounts);
rem = mod(totalTicks, maxcounts);
ticks = [overflows floor(rem)];
end

