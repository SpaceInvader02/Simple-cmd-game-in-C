#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <time.h>


typedef struct traffic_car
{
    int x, y;
} T_CAR;

char map[10][6];
char CAR = '^';
char TRAFFIC_CAR = '-';

int CAR_X = 1;

T_CAR traffic_car_1;
T_CAR traffic_car_2;
T_CAR traffic_car_3;

char key;
int IS_CRASHED = 0;
int RESPAWN_1 = 0, RESPAWN_2 = 0, RESPAWN_3 = 0;

int SCORE = 0;



void updateTraffic()
{
    traffic_car_1.y++;
    traffic_car_2.y++;
    traffic_car_3.y++;
}
//3 7 2   715
int not_correct_y(int y1, int y2, int y3)
{
    int cond1 = (y1 == y2 || y1 == y3 || y2 == y3);
    int r1 = y1 > y2 ? y1 - y2 : y2 - y1;
    int r2 = y1 > y3 ? y1 - y3 : y3 - y1;
    int r3 = y3 > y2 ? y3 - y2 : y2 - y3;
    int cond2 = (r1 < 2 || r2 < 2 || r3 < 2);

    return cond1 || cond2;
}   

int get_new_x(){
    int x = rand() % 2 + 1;
    return x;
}

int main()
{

    
    srand(time(NULL));
    do {
        traffic_car_1.y = rand() % 7 + 1;
        traffic_car_2.y = rand() % 7 + 1;
        traffic_car_3.y = rand() % 7 + 1;
    } while (not_correct_y(traffic_car_1.y, traffic_car_2.y, traffic_car_3.y));

    traffic_car_1.x = get_new_x();
    traffic_car_2.x = get_new_x();
    traffic_car_3.x = get_new_x();
    do {
        system("cls");
        printf("Use A/D to move\n");

        printf("SCORE: %d\n", SCORE);
        if (RESPAWN_1){
            traffic_car_1.x = get_new_x();
            RESPAWN_1 = 0;}
        if (RESPAWN_2){
            traffic_car_2.x = get_new_x();
            RESPAWN_2 = 0;}
        if (RESPAWN_3){
            traffic_car_3.x = get_new_x();
            RESPAWN_3 = 0;}

        if (IS_CRASHED)
        {
            printf("YOU CRASHED");
            break;
        }
        for (int i = 0; i < 10; i++)
        {
            if (i == 0)
                sprintf(map[i], " __ ");
            else if (i == 9)
                sprintf(map[i], " -- ");
            else
                sprintf(map[i], "|  |");
        }
        map[8][CAR_X] = CAR;

        map[traffic_car_1.y][traffic_car_1.x] = TRAFFIC_CAR;
        map[traffic_car_2.y][traffic_car_2.x] = TRAFFIC_CAR;
        map[traffic_car_3.y][traffic_car_3.x] = TRAFFIC_CAR;

        for (int i = 0; i < 10; i++)
        {
            printf(map[i]);
            printf("\n");
        }

        key = getch();

        int OLD_CAR_X = CAR_X;

        if (key == 'd') 
        {
            CAR_X++;
            updateTraffic();
        }
        if (key == 'a') 
        {
            CAR_X--;
            updateTraffic();
        }

        if (map[8][CAR_X] == '|')
            CAR_X = OLD_CAR_X;
        


        if (map[traffic_car_1.y][1] == '-')
        {
            traffic_car_1.y = 1;
            SCORE += 1;
            RESPAWN_1 = 1;
        }
        if (map[traffic_car_2.y][1] == '-')
        {
            traffic_car_2.y = 1;
            SCORE += 1;
            RESPAWN_2 = 1;
        }
        if (map[traffic_car_3.y][1] == '-')
        {
            traffic_car_3.y = 1;
            SCORE += 1;
            RESPAWN_3 = 1;
        }

        if ((traffic_car_1.x == CAR_X && traffic_car_1.y == 8) || (traffic_car_2.x == CAR_X && traffic_car_2.y == 8) || (traffic_car_3.x == CAR_X && traffic_car_3.y == 8))
            IS_CRASHED = 1;

        

    } while (key != 'q');
    return 0;
}
