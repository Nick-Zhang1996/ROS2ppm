# RC channel message
Header header

# No. of channels, this is better hard-coded since channel no is fixed at design and this way we don't mess with imemory allocation on embedded systems
# the value originates from PWM pulse width in us
# typical value 1000-2000, with 1500 being center of servo/zero input for throttle
uint16[4] ch
