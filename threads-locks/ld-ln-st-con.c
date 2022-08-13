/**
 * implement a lock using 
 * the load-linked and store-conditional
 * HW primitive instructions
 */

int *ptr = 0;
int loadLinked(int *ptr){
    return *ptr;
}

// this method represent an atomic 
// instruction of the HW
int storeConditional(int *ptr, int nval){
    if(*ptr == 0){ // such a cheeck should be performed by the HW, Iam only using this var to get the code to work.
        *ptr = nval;
        return 1;
    }
    else{
        return 0;
    }
}

void lock(int *ptr){
    while(storeConditional(ptr, 1) == 0)
        ; // spin
}

int unlock(int *ptr ){
    *ptr = 0;
}


int sharedVar = 0;
void work (){
    lock(ptr);
    sharedVar += 1;
    unlock(ptr); 
}

int main(){
    work();
    work();
}


// we need to loadLinked before the storeCOnditional
// to make a context for the HW. which helps in detecting
// the conflecting writes.


void lock(int *ptr){
    while(

        !(
            loadLinked(ptr) == 0 &&
            storeConditional(ptr, 1) == 1
        )
    )
    ; // spin
}


// a better version
void lock2(int *ptr){
    while(loadLinked(ptr) == 1 || storeConditional(ptr, 1) == 0)
        ; // spin
}