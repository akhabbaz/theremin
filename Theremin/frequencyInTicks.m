function [ticks] = frequencyInTicks(freq, divisor, maxcounts)
%  freq is in hz
% divisor is one of 1, 8, 64, 256, 1024
% maxcount is 256 or 65536
%  returns the ticks for a half wave at this frequency.
%
% ticks are overflows and ticks
if nargin < 3
    maxcounts = 256;
end
time = 1/freq/2;% time for a half wave
ticks = timeInTicks(time, divisor, maxcounts);
end

