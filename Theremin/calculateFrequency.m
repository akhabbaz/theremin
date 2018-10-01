% calculate time
freq = 500; % Hz
divisor = 8;
TperiodhalfDesired  = 1/freq/2;
clck = 16000000;
Tclck = 1/clck;

Tclck = divisor * Tclck;
ticks = TperiodhalfDesired/Tclck - 1;
ticks/256
mod(ticks, 256)

divisors = [ 1 8 64 256 1024];
 Tclcks = Tclck * divisors;