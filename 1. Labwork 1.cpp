#include<stdio.h>
#include<conio.h>
#include<graphics.h>
#include<math.h>
#include<dos.h>

void car(){
	setcolor(14);	//14 is yellow
	arc(200,450,30,180,70);	//roof of car
	line(260,415,290,415);	//front roof of car
	arc(290,423,0,90,8);	//small curve at front
	line(298,423,298,450);	//front part of car
	circle(280,450,15);	//tire 1
	circle(280,450,12);	//inside tire 1
	circle(150,450,15);	//tire 2
	circle(150,450,12);	//inside tire 2
	arc(200,450,30,150,59);	//for windows
	line(145,420,251,420);	//door line1
	line(200,391,200,443);	//door line2
	line(200,443,251,443);	//door lower line3
	line(251,420,251,443);	//front door line4
	line(130,450,135,450);	//lower back line
	line(165,450,265,450);	//lower middle line
	line(295,450,298,450);	//lower front line
	line(292,445,298,445);	//second lower front line
	//for mirror
	line(247,420,242,416);
	line(242,416,242,424);
	line(242,424,247,420);
	
	setfillstyle(SOLID_FILL,5);
	floodfill(137,430,14);	//car color
	floodfill(240,440,14);	//door
	setfillstyle(3,7);
	floodfill(196,410,14);
	floodfill(204,410,14);
	setfillstyle(11,7);
	floodfill(280,450,14);
	floodfill(150,450,14);
	
}

void backg(){
	setcolor(15);
	line(0,370,getmaxx(),370);	//road upper side
	line(0,490,getmaxx(),490);	//road lower side
	setfillstyle(SOLID_FILL,15);
	floodfill(100,450,0);	//top
	for(int i=0;i<getmaxx();i++){	//for road ko bich ko line
		if((i<=110||i>=320)&&i%30==0){
			line(i,430,i+9,430);
		}
	}
	//mountain
	line(0,199,200,100);	//first mountain left
	arc(220,157,49,118,60);	//first mountain tuppi
	line(259,112,460,300);	//first mountain right
	line(353,200,600,60);	//second mountain left
	arc(625,115,49,118,60);	//second moutain tuppi
	line(664,70,1000,200);	//second mountain right side
	
	setfillstyle(SOLID_FILL,10);
	floodfill(10,220,15);	//top
	
	setfillstyle(SOLID_FILL,LIGHTBLUE);
	floodfill(1,1,WHITE);
	
}

int obst(int d){
	setcolor(15);
	circle(700+d,280,8);	//red	//stop
	circle(700+d,300,8);	//yellow	//wait
	circle(700+d,320,8);	//green	//go
	rectangle(685+d,260,715+d,340);	//traffic box
	rectangle(695+d,340,705+d,370);	//traffic handle
	setfillstyle(SOLID_FILL,0);	//11 is light cyan
	floodfill(690+d,270,15);	//for traffic box
	setfillstyle(SOLID_FILL,7);	//7 is light gray
	floodfill(700+d,355,15);	//for traffic handle
	//intersection
	rectangle(730+d,490,850+d,getmaxy());	//intersected road
	for(int i=495;i<600;i++){
		if(i%30==0){
			line(790+d,i,790+d,i+9);	//road ko bich ko
		}
	}
	line(637+d,370,637+d,490);
	line(643+d,370,643+d,490);
	setfillstyle(SOLID_FILL,15);
	floodfill(640+d,400,15);
	
	setcolor(0);	//intersected part ko line hatauni
	line(730+d,490,850+d,490);
	
	setfillstyle(SOLID_FILL,GREEN);
	floodfill(700+d,500,15);
	floodfill(900+d,500,15);
	if(900+d<0)
		floodfill(500,500,15);
	
	return 637+d;
	
}

void traffic(int r,int d){
	if(r==0){
		setfillstyle(SOLID_FILL,4);	//red light
		floodfill(701+d,280,15);
		setfillstyle(SOLID_FILL,7);
		floodfill(700+d,300,15);
		floodfill(700+d,320,15);
	}
	else if(r==1){
		setfillstyle(SOLID_FILL,14);	//yellow light
		floodfill(700+d,300,15);
		setfillstyle(SOLID_FILL,7);
		floodfill(700+d,280,15);
		floodfill(700+d,320,15);
	}
	else if(r==2){
		setfillstyle(SOLID_FILL,3);	//green light
		floodfill(700+d,320,15);
		setfillstyle(SOLID_FILL,7);
		floodfill(700+d,280,15);
		floodfill(700+d,300,15);
	}
}
int zebracross(int d){
	//after 1300
	for(int i=380;i<=480;i+=27){
		setcolor(15);
		rectangle(1300+d,i,1450+d,17+i);
		setfillstyle(SOLID_FILL,WHITE);
		floodfill(1370+d,2+i,WHITE);
	}
	
	//for a person walking
}
int goal(int d){
	//after 1900
	setcolor(15);
	rectangle(1945+d,320,1955+d,370);
	settextstyle(1,0,1);
	outtextxy(1913+d,300,(char*)"GOAL");
	
	return 1945+d;
	
}

int main(){
	initwindow(1000,600,"AI CAR",70,50);
	int page=0,n=0;
	int check,color=0,count=0;			//for traffic light
	int countc=20,carPos = 300,isMoving=1;		//for car
	int zebracheck,checkgoal;

	while(n<3000)
	{
		setactivepage(page);
        setvisualpage(1-page);
		cleardevice();
		backg();
		check=obst(countc);
		checkgoal=goal(countc);
		traffic(color,countc);
		zebracheck=zebracross(countc);
		car();
		if(carPos/20 == check/20)
		{
			if(color == 0 && isMoving == 1)
			{
				isMoving = 0;
			}
			else if(color == 2 && isMoving == 0)
			{
				isMoving = 1;
			}		
		}
		
		if(carPos/20==checkgoal/20){
			isMoving=0;
			settextstyle(1,0,2);
			outtextxy(400,250,(char*)"GOAL REACHED!");
		}
		if(isMoving == 1)
			countc-=20;
		
		count++;
		if(count==30)
		{
			color = (color+1)% 3;
			count=0;
		}
		settextstyle(1,0,1);
		outtextxy(642,27,(char*)"Designed by: Shukrina Koju");
		outtextxy(723,47,(char*)"Roll Number: 19");
		page=(1-page);
		delay(100);
		n++;
	}setactivepage(1);
	getch();
	closegraph();
	return 0;
}
