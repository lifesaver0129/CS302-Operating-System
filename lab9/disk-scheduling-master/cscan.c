/*
  C-SCAN: Circular Scan
   - Scans towards the nearest end and works it way all the way to the end of the system.
   - Once it hits the bottom or top it jumps to the other end and moves in the same direction.
*/

#include <stdlib.h>
#include <stdio.h>

#define HIGH 199
#define LOW 0

int main(){
  int queue[20], q_size, head, i,j, seek=0, diff, max, temp, queue1[20], queue2[20], temp1=0, temp2=0;
  float avg;

  printf("%s\t", "Input no of disk locations");
  scanf("%d", &q_size);

  printf("%s\t", "Enter initial head position");
  scanf("%d", &head);

  printf("%s\n","Enter disk positions to be read");
  for(i=0; i<q_size; i++) {

    scanf("%d", &temp);
      if(temp >= head){
          queue1[temp1] = temp;
          temp1++;
      } else {
          queue2[temp2] = temp;
          temp2++;
      }
  }
  //sort both arrays
  for(i=0; i<temp1-1; i++){
    for(j=i+1; j<temp1; j++){
        if(queue1[i] > queue1[j]){
          temp = queue1[i];
          queue1[i] = queue1[j];
          queue1[j] = temp;
      }
    }
  }

  for(i=0; i<temp2-1; i++){
    for(j=i+1; j<temp2; j++){
      if(queue2[i]>queue2[j]){
          temp = queue2[i];
          queue2[i] = queue2[j];
          queue2[j] = temp;
      }
    }
  }

  //calculate closest edge
  if(abs(head-LOW) >= abs(head-HIGH)){

      for(i=1,j=0; j<temp1; i++,j++){
          queue[i] = queue1[j];
      }

          queue[i] = HIGH;
          queue[i+1] = 0;

      for(i=temp1+3, j=0; j<temp2; i++, j++){
          queue[i] = queue2[j];
      }

  } else {

      for(i=1,j=temp2-1; j>=0; i++,j--){
          queue[i] = queue2[j];
      }

          queue[i] = LOW;
          queue[i+1] = HIGH;

      for(i=temp2+3, j=temp1-1; j>=0; i++, j--){
          queue[i] = queue1[j];
      }
}

  queue[0] = head;

  for(j=0; j<=q_size+1; j++){
      diff=abs(queue[j+1] - queue[j]);
        seek += diff;
        printf("Disk head moves from %d to %d with seek %d\n",queue[j],queue[j+1],diff);

  }

  //seek = seek - max; //subtract seek time back to zero
  printf("Total seek time is %d\n", seek);
  avg = seek/(float)q_size;
  printf("Average seek time is %f\n", avg);

  return 0;
}
