#include "dynamic_array.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <cfloat>

/* private functions *********************************************************/

/* Position in the buffer of the array element at position index */
static int index_to_offset ( const DynamicArray * da, int index ) {
    return index + da->origin;
}

/* Position of the element at buffer position 'offset' */
static int offset_to_index ( const DynamicArray * da, int offset ) {
    return offset - da->origin;
}

/* Non-zero if and only if offset lies ouside the buffer */
static int out_of_buffer ( DynamicArray * da, int offset ) {
    return offset < 0 || offset >= da->capacity;
}

/* Makes a new buffer that is twice the size of the old buffer,
   copies the old information into the new buffer, and deletes
   the old buffer */
static void extend_buffer ( DynamicArray * da ) {

    double * temp = (double *) calloc ( 2 * da->capacity, sizeof(double) );
    int new_origin = da->capacity - (da->end - da->origin)/2,
           new_end = new_origin + (da->end - da->origin);

    for ( int i=0; i<DynamicArray_size(da); i++ ) {
        temp[new_origin+i] = DynamicArray_get(da,i);
    }

    free(da->buffer);
    da->buffer = temp;

    da->capacity = 2 * da->capacity;
    da->origin = new_origin;
    da->end = new_end;

    return;

}

/* public functions **********************************************************/

DynamicArray * DynamicArray_new(void) {
    static DynamicArray ** arrays = (DynamicArray **) malloc(sizeof(DynamicArray));
    DynamicArray * da = (DynamicArray *) malloc(sizeof(DynamicArray));
    da->capacity = DYNAMIC_ARRAY_INITIAL_CAPACITY;    
    da->buffer = (double *) calloc ( da->capacity, sizeof(double) ); 
    da->origin = da->capacity / 2;
    da->end = da->origin;

    numArrays++;
    //printf("New array func called, num %d\n", numArrays);
    return da;
}

void DynamicArray_destroy(DynamicArray * da) {
    free(da->buffer);
    da->buffer = NULL;
    numArrays--;
    //printf("Destroy array func called, num %d\n", numArrays);
    return;
}

int DynamicArray_size(const DynamicArray * da) {
    assert(da->buffer != NULL);
    return da->end - da->origin;
}

char * DynamicArray_to_string(const DynamicArray * da) {
    assert(da->buffer != NULL);
    char * str = (char *) calloc (20,DynamicArray_size(da)),
         temp[20];
    int j = 1;
    str[0] = '[';
    for ( int i=0; i < DynamicArray_size(da); i++ ) {
        if ( DynamicArray_get(da,i) == 0 ) {
            snprintf ( temp, 20, "0" );
        } else {
            snprintf ( temp, 20, "%.5lf", DynamicArray_get(da,i) ); 
        }
        if ( i < DynamicArray_size(da) - 1 ) {
            sprintf( str + j, "%s,", temp);
            j += strlen(temp) + 1;
        } else {
            sprintf( str + j, "%s", temp);
            j += strlen(temp);
        }

    }
    str[j] = ']';
    return str;
}

void DynamicArray_print_debug_info(const DynamicArray * da) {

    char * s = DynamicArray_to_string(da);
    printf ( "  %s\n", s);
    printf ( "  capacity: %d\n  origin: %d\n  end: %d\n  size: %d\n\n",
      da->capacity, 
      da->origin, 
      da->end,
      DynamicArray_size(da));

    free(s);

}

void DynamicArray_set(DynamicArray * da, int index, double value) {
    assert(da->buffer != NULL);
    assert ( index >= 0 );
    while ( out_of_buffer(da, index_to_offset(da, index) ) ) {
        extend_buffer(da);
    }
    da->buffer[index_to_offset(da, index)] = value;
    if ( index >= DynamicArray_size(da) ) {
        da->end = index_to_offset(da,index+1);
    }

}

double DynamicArray_get(const DynamicArray * da, int index) {
    assert(da->buffer != NULL);
    assert ( index >= 0 );
    if ( index >= DynamicArray_size(da) ) {
        return 0;
    } else {
        return da->buffer[index_to_offset(da,index)];
    }
}

void DynamicArray_push(DynamicArray * da, double value ) {
    DynamicArray_set(da, DynamicArray_size(da), value );
}

void DynamicArray_push_front(DynamicArray * da, double value) {
    assert(da->buffer != NULL);
    while ( da->origin == 0 ) {
        extend_buffer(da);
    }
    da->origin--;
    DynamicArray_set(da,0,value);
}

double DynamicArray_pop(DynamicArray * da) {
    assert(DynamicArray_size(da) > 0);
    double value = DynamicArray_last(da);
    DynamicArray_set(da, DynamicArray_size(da)-1, 0.0);
    da->end--;
    return value;
}

double DynamicArray_pop_front(DynamicArray * da) {
    assert(DynamicArray_size(da) > 0);
    double value = DynamicArray_first(da);
    da->origin++;
    return value;    
}

DynamicArray * DynamicArray_map(const DynamicArray * da, double (*f) (double)) {
    assert(da->buffer != NULL);
    DynamicArray * result = DynamicArray_copy(da);
    for ( int i=0; i<DynamicArray_size(da); i++ ) {
        DynamicArray_set(result, i, f(DynamicArray_get(da, i)));
    }
    //numArrays--;
    return result;
}

DynamicArray * DynamicArray_subarray(DynamicArray * da, int a, int b) {

  assert(da->buffer != NULL);
  assert(b >= a);

  DynamicArray * result = DynamicArray_new();

  for (int i=a; i<b; i++) {
      DynamicArray_push(result,DynamicArray_get(da, i));
  }

  return result;

}

/*! Mathematical operations */
double DynamicArray_min ( const DynamicArray * da ) {
    assert(DynamicArray_size(da) > 0);
    double value = DBL_MAX;
    for ( int i=0; i < DynamicArray_size(da); i++ ) {
        if (DynamicArray_get(da,i) < value ){
            value = DynamicArray_get(da,i);
        }
    }
    return value;  
}

double DynamicArray_max ( const DynamicArray * da ) {
    assert(DynamicArray_size(da) > 0);
    double value = DBL_MIN;
    for ( int i=0; i < DynamicArray_size(da); i++ ) {
        if (DynamicArray_get(da,i) > value ){
            value = DynamicArray_get(da,i);
        }
    }
    return value;    
}

double DynamicArray_mean ( const DynamicArray * da ) {
    assert(DynamicArray_size(da) > 0);
    double sum = 0;
    for ( int i=0; i < DynamicArray_size(da); i++ ) {
        sum += DynamicArray_get(da,i);
    }
    double value = sum/DynamicArray_size(da);
    return value;     
}

double DynamicArray_median ( const DynamicArray * da ) {
    assert(DynamicArray_size(da) > 0);
    double value = 0;
    double midIndex = DynamicArray_size(da)/2;
    DynamicArray * new_da = DynamicArray_sort(da);
    //even number size
    if (DynamicArray_size(da)%2 == 0) {
        //printf("even size: %lf and %lf\n",DynamicArray_get(da,midIndex-1), DynamicArray_get(da,midIndex) );
        value = (DynamicArray_get(new_da,midIndex-1) + DynamicArray_get(new_da,midIndex) ) / 2;
    } else {
        //printf("odd size: %lf \n",midIndex);
        value = (DynamicArray_get(new_da,midIndex));
    }
    DynamicArray_destroy(new_da);
    return value;   
}

double DynamicArray_sum ( const DynamicArray * da ) {
    double value = 0;
    if (DynamicArray_size(da) == 0) {
        return value;
    } else {
        for ( int i=0; i < DynamicArray_size(da); i++ ) {
            value += DynamicArray_get(da,i);
        }
    }
    return value;

}


double DynamicArray_first ( const DynamicArray * da ) {
    assert(DynamicArray_size(da) > 0);
    return DynamicArray_get(da, 0);
}

double DynamicArray_last ( const DynamicArray * da ) {
    assert(DynamicArray_size(da) > 0);
    return DynamicArray_get(da, DynamicArray_size(da)-1);
}

DynamicArray * DynamicArray_copy ( const DynamicArray * da ) {
    DynamicArray * new_da = DynamicArray_new();
    for ( int i=0; i < DynamicArray_size(da); i++ ) {
        DynamicArray_push(new_da, DynamicArray_get(da,i));
        }

    return new_da;
}

DynamicArray * DynamicArray_range ( double a, double b, double step) {
    DynamicArray * new_da = DynamicArray_new();

    if (step > 0){
        if (step > (b -a)){ //step is too big
            return new_da;
        }
        for ( double val=a; val <= b; val += step){
            DynamicArray_push(new_da, val);
        }
    } else if (step < 0) {
        if (step < (b -a)){ //step is too big (negative)
            return new_da;
        }
        for ( double val=a; val >= b; val += step){
            DynamicArray_push(new_da, val);
        }
    }

    return new_da;
}

DynamicArray * DynamicArray_sort (const DynamicArray * da ) {
    double temp;
    int i, j;
    DynamicArray * new_da = DynamicArray_copy(da);
    for (i = 0; i < DynamicArray_size(new_da); i++){
	    for (j = i + 1; j < DynamicArray_size(new_da); j++){
		    if(DynamicArray_get(new_da,i) > DynamicArray_get(new_da,j)){
			    temp = DynamicArray_get(new_da,i);
			    DynamicArray_set(new_da,i,DynamicArray_get(new_da,j));
			    DynamicArray_set(new_da,j,temp);
		    }
	    }
    }
    return new_da;
}

DynamicArray * DynamicArray_concat ( const DynamicArray * a, const DynamicArray * b ) {
    assert(a->buffer != NULL);
    assert(b->buffer != NULL);
    DynamicArray * new_da = DynamicArray_copy(a);
    //add values from second array
    for ( int i=0; i < DynamicArray_size(b); i++ ) {
        DynamicArray_push(new_da, DynamicArray_get(b,i));
    }
    //printf("Concat FUNC before sort string: %s\n", DynamicArray_to_string(new_da)); 
    new_da = DynamicArray_sort(new_da);
    //printf("Concat FUNC after sort string: %s\n", DynamicArray_to_string(new_da)); 
    numArrays--; /* sorts adds an 'extra' array, so delete */
    return new_da;
}


DynamicArray * DynamicArray_take ( const DynamicArray * da, int n ) {
    assert(da->buffer != NULL);
    DynamicArray * new_da = DynamicArray_new();
    int i;
    if (n > 0){
        for ( i=0; i < n; i++ ) {
            if ( i > DynamicArray_size(da)){
                DynamicArray_push(new_da, 0);
            } else {
            DynamicArray_push(new_da, DynamicArray_get(da,i));
            }
        }
    } else if (n < 0){
        for ( i=n; i < 0; i++ ) {
            if ( DynamicArray_size(da) + i < 0){
                DynamicArray_push(new_da, 0);
            } else {
            DynamicArray_push(new_da, DynamicArray_get(da,DynamicArray_size(da) + i));
            }
        }
    } 

    return new_da;
    
}

int DynamicArray_num_arrays() {
    return numArrays;
}

int DynamicArray_is_valid(const DynamicArray * da) {
    if (da->buffer != NULL) {
        return 1;
    } else {
        return 0;
    }
}

  