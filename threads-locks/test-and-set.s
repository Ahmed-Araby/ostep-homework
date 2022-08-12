# my result about quantifying the cpu inefficiency.
# the criteria I used, is to calculate all 
# the instructions executed by a thread and
# the useless instructions used by the same thread
# and it truned out for this program, that as long as
# the threads as contending for the lock
# the uselss instruction will be about 0.4 = 40% of
# the all the instructions executed by the thread
# again theses numbers are relative
# to this program
# and when running 2 threads
# with interrupt happing each 1 instruction
# and for any amount of iterations
# but iterations has to be the same for both threads
# for them to keep contending 

# %fx register will hold count of
# all the instruction exection that 
# happened in the program
mov $0, %fx

# %ex register whill hold the 
# count of the usless instruction execution
# initialize the register 
# that will hold useless instuction 
# execution of the .acquire section 
# a useless exection of the .acquire section
# is any exection after the 'jne .acquire'
# line have been executed
mov $0, %ex

.var mutex
.var count

.main
.top	




.acquire
mov  $1, %ax        
xchg %ax, mutex     # atomic swap of 1 and mutex
test $0, %ax        # if we get 0 back: lock is free!
add $4, %ex         # do not count this instruction
add $4, %fx         # do not count this instrution
jne  .acquire       # if not, try again

# remove the very first loop as it is necessary to 
# acquire the lock or in an efficient locking 
# support will send the thread to sleep
sub $4, %ex

# critical section
mov  count, %ax     # get the value at the address
add  $1, %ax        # increment it
mov  %ax, count     # store it back

# release lock
mov  $0, mutex

# see if we're still looping
sub  $1, %bx
test $0, %bx

# count critical section + lock release +   looping
add $7, %fx         # do not count this instruction

jgt .top	

# count the halt instruction
add $1, %fx

halt
