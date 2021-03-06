#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define bold      "\33[1m"
#define underline "\33[4m"
#define unformat  "\33[0m"
#define rook	 	"\u265C"
#define knite	 	"\u265e"
#define bishop		"\u265D"
#define qween		"\u265A"
#define king		"\u265B"
#define pion		"\u265F"
#define space 		" "
		      //printf("%c[%d;%df ",0x1B,y,x);
#define print(tool)	printf("%c[%d;%d;%dm %s ",'\e',at,txt,bg,tool)
#define change_bg	(bg==yellow_b)?(bg=cyan_b):(bg=yellow_b)
#define change_tx	(chessb[i][j]>97)?(txt=white_t):(txt=black_t)

#define START_GAME 1    //define statement
#define MENU_2 2
#define MENU_3 3
#define MENU_4 4
#define QUIT 0
#define WHITE 0
#define BLACK 1

typedef enum color_attributes {all_off,bold_on,Underscore=4,blink_on,rev_video_on=7,con_on} color_a;
typedef enum color_txt {black_t=30,red_t,green_t,yellow_t,blue_t,magenta_t,cyan_t,white_t=97} color_t;
typedef enum color_bg {black_b=40,red_b,green_b,yellow_b,blue_b,magenta_b,cyan_b,white_b=107} color_b;

void showchessboard (unsigned char chessb[ ][8]);
void initboard(char * chessb );
void gotoxy(int x,int y);
int menu();
int game_start();
int menu_2();
int menu_3();
int menu_4();
void quit();
int make_turn(int player_color);

unsigned char chess[8][8];
int result=0;
int player_color=0;

int main()
{

	int choice;

	initboard((char*)chess);
	choice = menu();

	while(choice != QUIT)//execute so long as choice is not equal to QUIT
	{
		switch(choice)
			{
				case START_GAME:
					game_start();
					break;
				case QUIT: quit();
					break;
				default:
					printf("Oops! An invalid choice slipped through. ");
					printf("Please try again.\n");
			}
		choice = menu(); /* get user's subsequent selections */
	}
	return 0;
}

//////////////////////////////////////////////////////////////////

void initboard(char* chessb)
{
	char chess[][8]={{'r','n','b','q','k','b','n','r'},
					{'p','p','p','p','p','p','p','p'},
					{' ',' ',' ',' ',' ',' ',' ',' '},
					{' ',' ',' ',' ',' ',' ',' ',' '},
					{' ',' ',' ',' ',' ',' ',' ',' '},
					{' ',' ',' ',' ',' ',' ',' ',' '},
					{'P','P','P','P','P','P','P','P'},
					{'R','N','B','Q','K','B','N','R'}};
	char* temp=(char*)chess;
	while((temp-(char*)chess)<64)*chessb++=*temp++;
}


 //////////////////////////////////////////////////////////////////////////////////////////////

void showchessboard(unsigned char chessb[ ][8])
{
	char i,j;
	color_t txt;		// color text
	color_b bg;		// color background
	color_a at=all_off;	//attributes
	system("clear");
	printf("\e[%d;%dm\n\n\n\n\t\t   A  B  C  D  E  F  G  H\n",at,red_t);
	for(i=7;i>-1;i--)	//rows
	{
		change_bg;
		printf("\e[%d;%dm\t\t%c ",at,red_t,49+i);//the number on the left side
		for(j=0;j<8;j++)
		{  //collums
			change_bg;
			change_tx; // if needed
			switch(chessb[i][j]){
				case 'r':print(rook);
					break;
				case 'n': print(knite);
					break;
				case 'b': print(bishop);
					break;
				case 'q': print(qween);
					break;
				case 'k':print(king);
					break;
				case 'p': print(pion);
					break;
				case 'R': print(rook);
					break;
				case 'N':print(knite);
					break;
				case 'B':print(bishop);
					break;
				case 'Q':print(qween);
					break;
				case 'K':print(king);
					break;
				case 'P':print(pion);
					break;
				default :print(space);
			}

		}
		printf("\e[%d;%dm %d\n  ",at,red_t,i+1);//the number on the right side
        }
        printf("%c[%d;%dm\t\t   A  B  C  D  E  F  G  H\n\n\n\n",'\e',at,red_t);
	printf("%c[%d;%dm",'\e',at,green_t);//back to default black text
}
 //////////////////////////////////////////////////////////////////////////////////////////////

void gotoxy(int x,int y)
{
	printf("%c[%d;%df ",0x1B,y,x);
}

//////////////////////////////////////////////////////////////////////////////////////////////

int menu(void)
{
    int option;

    printf("Chess game\n\n");
    printf("1.\tStart the game\n");
    printf("0.\tQuit\n\n");
    printf("Make your selection: ");

    while( (scanf(" %d", &option) != 1) || (option < 0) || (option > 4))
    {
      fflush(stdin);                    /* clear bad data from buffer */
      printf("That selection isn't valid. Please try again.\n\n");
      printf("Your choice? ");
    }
    return option;
}
/////////////////////////////////////////////////////////////////////////////////////////////
int game_start()
{
	printf("Game started\n");
	getchar();
	system("clear");
	showchessboard(chess);
	while (!result)
	{
		printf("\n\nPlayer 1 please make your turn:\n");
		result=make_turn(WHITE);
		if (result) break;
		printf("\n\nPlayer 2 please make your turn:\n");
		result=make_turn(BLACK);
		if (result) break;
	}
	return 0;
}
void quit()
{
	printf("Quiting...Bye!");
	exit(0);
}
bool move_figure(int f_x, int f_y,int t_x,int t_y)
{

    chess[t_x][t_y]=chess[f_x][f_y];
    chess[f_x][f_y]=' ';
    getchar();

    return true;
}
int validate_rook_move(int player_color, int f_x, int f_y, int t_x, int t_y)
{
    if (f_x == t_x && f_y == t_y)
    {
        return false;
    }
    else if (f_x == t_x && f_y != t_y)
    {
        if (f_y > t_y)
            while ((f_y - 1) != t_y)
                {
                    if (chess[f_x][f_y] != ' ') return false;
                    f_y -= 1;
                }
        else if (f_y < t_y)
        {
            /* code */
        }
        
    }
    
    return true;
}
int make_turn(int player_color)
{
	unsigned int f_y=0,t_y=0;
	unsigned char f_x=0,t_x=0;
	bool bMoveReaded=false, bFigureMoved=false, bDestOccupied = false, bValidMove = false;
	int i=0,j=0;

	do
	{
        do
        {
            fflush(stdin);
            scanf("%c%d%c%d",&f_x,&f_y,&t_x,&t_y);
            if((f_y>0 && f_y<9) &&(t_y>0&&t_y<9))
                if (((f_x>64 && f_x<73) &&(t_x>64&&t_x<73))||((f_x>96 && f_x<105) &&(t_x>96&&t_x<105)))
                {
                    bMoveReaded=true;
                    printf("From %c:%d to %c:%d\n",f_x,f_y,t_x,t_y);
                }
                else printf("Input again\n");
            else printf("Input again\n");
        } while(!bMoveReaded);
        //correcting user input to access element in array
        if (f_x>64 && f_x<73) f_x-=65;
        else f_x-=97;
        if (t_x>64&&t_x<73) t_x-=65;
        else t_x-=97;
        f_y-=1;
        t_y-=1;
        //*end correcting user input to access element in array
        switch(chess[f_y][f_x])
        {
            case 'r':   if(!player_color) 
                        {
                            bValidMove = validate_rook_move(player_color,f_y,f_x,t_y,t_x);
                            bFigureMoved = move_figure(f_y,f_x,t_y,t_x);
                        }
                        else
                        {
                            printf("Choose your figure!");
                            getchar();
                        }
                        break;
            case 'n':	if(!player_color) bFigureMoved=move_figure(f_y,f_x,t_y,t_x);
                        else
                        {
                            printf("Choose your figure!");
                            getchar();
                        }
                        break;
            case 'b':	if(!player_color) bFigureMoved=move_figure(f_y,f_x,t_y,t_x);
                        else
                        {
                            printf("Choose your figure!");
                            getchar();
                        }
                        break;
            case 'q':	if(!player_color) bFigureMoved=move_figure(f_y,f_x,t_y,t_x);
                        else
                        {
                            printf("Choose your figure!");
                            getchar();
                        }
                        break;
            case 'k':	if(!player_color) bFigureMoved=move_figure(f_y,f_x,t_y,t_x);
                        else
                        {
                            printf("Choose your figure!");
                            getchar();
                        }
                        break;
            case 'p':	if(!player_color) bFigureMoved=move_figure(f_y,f_x,t_y,t_x);
                        else
                        {
                            printf("Choose your figure!");
                            getchar();
                        }
                        break;
            case 'R':	if(player_color) bFigureMoved=move_figure(f_y,f_x,t_y,t_x);
                        else
                        {
                            printf("Choose your figure!");
                            getchar();
                        }
                        break;
            case 'N':	if(player_color) bFigureMoved=move_figure(f_y,f_x,t_y,t_x);
                        else
                        {
                            printf("Choose your figure!");
                            getchar();
                        }
                        break;
            case 'B':	if(player_color) bFigureMoved=move_figure(f_y,f_x,t_y,t_x);
                        else
                        {
                            printf("Choose your figure!");
                            getchar();
                        }
                        break;
            case 'Q':	if(player_color) bFigureMoved=move_figure(f_y,f_x,t_y,t_x);
                        else
                        {
                            printf("Choose your figure!");
                            getchar();
                        }
                        break;
            case 'K':	if(player_color) bFigureMoved=move_figure(f_y,f_x,t_y,t_x);
                        else
                        {
                            printf("Choose your figure!");
                            getchar();
                        }
                        break;
            case 'P':	if(player_color) bFigureMoved=move_figure(f_y,f_x,t_y,t_x);
                        else
                        {
                            printf("Choose your figure!");
                            getchar();
                        }
                        break;
        }
    system("clear");
    showchessboard(chess);
    } while(!bFigureMoved);
    return 0;
}
