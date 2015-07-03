#include "poker.h"


int send_msg(int command,int num)
{
	int cmd = command;
	char msgbuff[50]={'\0'};
	switch(command)
	{
		case CALL:
			{
				memcpy(msgbuff,"call \n",6);
				write(sockfd,msgbuff, 6);
				break;	
			}
		case CHECK:
			{
				memcpy(msgbuff,"check \n",7);
				write(sockfd,msgbuff, 7);
				break;	
			}
		case ALLIN:
			{
				memcpy(msgbuff,"all_in \n",8);
				write(sockfd,msgbuff, 8);
				break;	
			}
		case FOLD:
			{
				memcpy(msgbuff,"fold \n",6);
				write(sockfd,msgbuff, 6);
				break;	
			}
		case RAISE:
			{
				//memcpy(msgbuff,"raise \n",7);
				snprintf(msgbuff,50,"raise %d \n",num);
				write(sockfd,msgbuff, strlen(msgbuff));
				break;	
			}
		default: break;
	}
	return cmd;

}

void check_msg_start(char c)
{
	for(int i=0;i<4;i++)
	{
		b_reg[i]=b_reg[i+1];
	}
	b_reg[4]=c;

	if(b_reg.compare("over ")==0)
	{
		process = GAMEOVER;
	}
	if(b_reg.compare("uire/")==0)
	{
		process = INQ_PRO;
	}
	if(b_reg.compare("lind/")==0)
	{
		process = BLIND_PRO;
	}
	if(b_reg.compare("hold/")==0)
	{
		process = HOLD_PRO;
	}
	if(b_reg.compare("seat/")==0)
	{
		process = SEAT_PRO;
	}
	if(b_reg.compare("flop/")==0)
	{
		process = FLOP_PRO;
	}
	if(b_reg.compare("turn/")==0)
	{
		process = TURN_PRO;
	}
	if(b_reg.compare("iver/")==0)
	{
		process = RIVER_PRO;
	}
	if(b_reg.compare("-win/")==0)
	{
		process = POT_PRO;
	}
}
int check_msg_end(char c)
{
	for(int i=0;i<4;i++)
	{
		b_reg[i]=b_reg[i+1];
	}
	b_reg[4]=c;

	if(b_reg.compare("/seat")==0)
	{
		return SEAT_END;
	}
	if(b_reg.compare("/blin")==0)
	{
		return BLIND_END;
	}
	if(b_reg.compare("/hold")==0)
	{
		return HOLD_END;
	}
	if(b_reg.compare("/flop")==0)
	{
		return FLOP_END;
	}
	if(b_reg.compare("/turn")==0)
	{
		return TURN_END;
	}
	if(b_reg.compare("/rive")==0)
	{
		return RIVER_END;
	}
	if(b_reg.compare("/inqu")==0)
	{
		return INQ_END;
	}
	return NO_END;
}

char num_to_abc(char num)
{                                  //2_3_...10_J_Q_K_A
	char b;						   //to
	if((num>='2')&&(num<='9'))	   //A_B_...I_J_K_L_M
		b = (char)(num +15);
	if(num == '0')
		b=(char)73;
	if(num == 'J')
		b=(char)74;
	if(num == 'Q')
		b=(char)75;
	if(num == 'K')
		b=(char)76;
	if(num == 'A')
		b=(char)77;
	return b;
}

void catch_msg_blind()
{
	int i=0;
	while(msg_reg[i++] != ':');
	i++;
	while (msg_reg[i] != ' ')
	{
		g.add_sblind(msg_reg[i++]);
	}
	i+=2;
	if(msg_reg[i] != '/')
	{
		while(msg_reg[i++] != ':');
		i++;
		while (msg_reg[i] != ' ')
		{
			g.add_bblind(msg_reg[i++]);
		}
	}
	
}
void catch_msg_hold()
{
	int i=0;
	char c;
	i+=2;
	while(1)
	{
		c = msg_reg[i];
		if(c == SPADES)
			g.add_h_card(c,COLOR);
		else if(c == HEARTS)
			g.add_h_card(c,COLOR);
		else if(c == CLUBS)
			g.add_h_card(c,COLOR);
		else if(c == DIAMONDS)
			g.add_h_card(c,COLOR);
		while(msg_reg[i++]!=' ');
		if(msg_reg[i]!='1')
			g.add_h_card(num_to_abc(msg_reg[i]),POINT);
		else if((msg_reg[i++]=='1')&&(msg_reg[i]=='0'))
			g.add_h_card('I',POINT);
		while(msg_reg[i++]!='\n');
		if(msg_reg[i]=='/')
			break;
	}
}

void catch_msg_turn()
{
	int i=0;
	char c;
	i+=2;
	while(1)
	{
		c = msg_reg[i];
		if(c == SPADES)
			g.add_t_card(c,COLOR);
		else if(c == HEARTS)
			g.add_t_card(c,COLOR);
		else if(c == CLUBS)
			g.add_t_card(c,COLOR);
		else if(c == DIAMONDS)
			g.add_t_card(c,COLOR);
		while(msg_reg[i++]!=' ');
		if(msg_reg[i]!='1')
			g.add_t_card(num_to_abc(msg_reg[i]),POINT);
		else if((msg_reg[i++]=='1')&&(msg_reg[i]=='0'))
			g.add_t_card('I',POINT);
		while(msg_reg[i++]!='\n');
		if(msg_reg[i]=='/')
			break;
	}
}

void catch_msg_flop()
{
	int i=0;
	char c;
	i+=2;
	while(1)
	{
		c = msg_reg[i];
		if(c == SPADES)
			g.add_f_card(c,COLOR);
		else if(c == HEARTS)
			g.add_f_card(c,COLOR);
		else if(c == CLUBS)
			g.add_f_card(c,COLOR);
		else if(c == DIAMONDS)
			g.add_f_card(c,COLOR);
		while(msg_reg[i++]!=' ');
		if(msg_reg[i]!='1')
			g.add_f_card(num_to_abc(msg_reg[i]),POINT);
		else if((msg_reg[i++]=='1')&&(msg_reg[i]=='0'))
			g.add_f_card('I',POINT);
		while(msg_reg[i++]!='\n');
		if(msg_reg[i]=='/')
			break;
	}
}

void catch_msg_river()
{
	int i=0;
	char c;
	i+=2;
	while(1)
	{
		c = msg_reg[i];
		if(c == SPADES)
			g.add_r_card(c,COLOR);
		else if(c == HEARTS)
			g.add_r_card(c,COLOR);
		else if(c == CLUBS)
			g.add_r_card(c,COLOR);
		else if(c == DIAMONDS)
			g.add_r_card(c,COLOR);
		while(msg_reg[i++]!=' ');
		if(msg_reg[i]!='1')
			g.add_r_card(num_to_abc(msg_reg[i]),POINT);
		else if((msg_reg[i++]=='1')&&(msg_reg[i]=='0'))
			g.add_r_card('I',POINT);
		while(msg_reg[i++]!='\n');
		if(msg_reg[i]=='/')
			break;
	}
}

void catch_msg_inq()
{
	int i=0;
	char msg_char;
	while(1)
	{
		while(msg_reg[i++] != '\n');
		if(msg_reg[i]=='t')
			break;
		while(msg_reg[i++] != ' ');
		while(msg_reg[i++] != ' ');
		while(msg_reg[i++] != ' ');
		while(msg_reg[i++] != ' ');
		msg_char = msg_reg[i];
		switch(msg_char)
		{
			case ALL_IN_PAC:
				{
					g.add_play_ac(ALL_IN_PAC);
					g.play_all = 1;//someone all_in
					continue;
				}
			case BLIND_PAC:
				{
					g.add_play_ac(BLIND_PAC);
					continue;
				}
			case CHECK_PAC:
				{
					g.add_play_ac(CHECK_PAC);
					continue;
				}
			case RAISE_PAC:
				{
					g.add_play_ac(RAISE_PAC);
					continue;
				}
			case FOLD_PAC:
				{
					g.add_play_ac(FOLD_PAC);
					continue;
				}
			default: continue;
		}
	}

}
int find_simgle()
{
	int flag =0;
	/*
	if((g.h_card.point=="LM")||(g.h_card.point=="ML"))  //find A K
		flag = 1;
	if((g.h_card.point=="KL")||(g.h_card.point=="LK"))  //find K Q
		flag = 1;
	*/
	if((g.h_card.point[0]>='J')||(g.h_card.point[1]>='J'))
		flag =1;
	return flag;
}
int check_flop()
{
	int flag=0;
	string p=g.h_card.point + g.f_card.point;
	string c=g.h_card.color  + g.f_card.color;
	sort(p.begin(),p.end());
	sort(c.begin(),c.end());
	if(c[0]==c[4]) //same color
		flag=1;
		
	for(int i=4;i>0;i--) //shunzi
		{
			if(p[i] != (char)(p[i-1] +1))
				break;
			if(i==1)
				flag=1;
		}
	//number of word	
	string w; //word
	string n;  //number
	char cnt='1';
	int j;
	char base=p[0];
	for(j=1;j<5;j++)
		{		
			if(base == p[j])
			{
				++cnt;
			}
			else
			{
				w.push_back(base);
				n.push_back(cnt);
				base = p[j];
				cnt = '1';			
			}
			if(cnt!='1' && j==4)
			{
				w.push_back(base);
				n.push_back(cnt);
				base = p[j];
				cnt = '1';	
			}
		}
	for(j=0;j<n.size();j++)
	{
		if(n[j]>='3')
			flag =1;
		if((n[j]=='2')&&(w[j]>='J'))
			flag=1;
	}
	return flag;
}
void action()
{
	int cmd_buff;
	if(g.foldcard != FOLD)	
	{
		switch (g.process_cnt)
		{
			case INQ_preflop:
				{
					if(g.play_all!=1)
					{
						if((g.h_card.point=="MM")||(g.h_card.point=="LL")||(g.h_card.point=="KK"))
						{
							cout<<"bingo AAKKQQ"<<endl;
							if(ac_time--)
								cmd_buff = send_msg(RAISE,1);
							else
							{
								ac_time=2;
								cmd_buff = send_msg(CALL,0);
							}
						}
						else if((g.h_card.color=="SS")||(g.h_card.color=="HH")  \
									||(g.h_card.color=="CC")||(g.h_card.color=="DD"))
							{
								cout<<"bingo SSHHCCDD"<<endl;
								if(ac_time--)
									cmd_buff = send_msg(RAISE,1);
								else
								{
									ac_time=2;
									cmd_buff = send_msg(CALL,0);
								}
							}
						//else if(find_simgle())
						//	cmd_buff = send_msg(CALL,0);
						else
							cmd_buff = send_msg(CALL,0);
					}
					else
						cmd_buff = send_msg(FOLD,0);
						
						//cmd_buff = send_msg(CALL,0);
					break;
				}
			case INQ_flop:
				{
					if(check_flop())
						cmd_buff = send_msg(RAISE,0);
					else
						//cmd_buff = send_msg(FOLD,0);
						cmd_buff = send_msg(CALL,0);
					
					break;
				}
			case INQ_turn:
				{
					cmd_buff = send_msg(CALL,5);
					break;
				}
			case INQ_river:
				{
					cmd_buff = send_msg(CALL,5);
					break;
				}
			default: break;

		}
		g.foldcard_change(cmd_buff);
	}
}
void get_seat_info(char buff)
{
	int c=check_msg_end(buff);
	msg_reg.push_back(buff);
	if(c == SEAT_END)
	{
		//catch_msg_seat();
		cnt=0;
		process = IDEL;
		g.process_reg = SEAT_PRO;
		g.foldcard_change(NOFOLD);
		msg_reg.clear();
	}
}
void get_blind_info(char buff)
{
	int c=check_msg_end(buff);
	msg_reg.push_back(buff);
	if(c == BLIND_END)
	{
		catch_msg_blind();   //¾²Ì¬¶Ô»º´æ½âÎö
		cnt=0;
		process = IDEL;
		g.process_reg = BLIND_PRO;

		msg_reg.clear();
	}
}

void get_hold_info(char buff)
{
	int c=check_msg_end(buff);
	msg_reg.push_back(buff);
	if(c == HOLD_END)
	{
		catch_msg_hold();   //¾²Ì¬¶Ô»º´æ½âÎö
		cnt=0;
		process = IDEL;
		g.process_reg = HOLD_PRO;
		g.process_cnt_change(INQ_preflop);
		msg_reg.clear();
	}
}

void get_inq_info(char buff)
{
	int c=check_msg_end(buff);
	msg_reg.push_back(buff);
	if(c == INQ_END)
	{
		catch_msg_inq();   //¾²Ì¬¶Ô»º´æ½âÎö
		
		action();
		//send_msg(CALL,0);
		cnt=0;
		process = IDEL;
		g.process_reg = INQ_PRO;
		msg_reg.clear();
	}
}
void get_turn_info(char buff)
{
	int c=check_msg_end(buff);
	msg_reg.push_back(buff);
	if(c == TURN_END)
	{
		catch_msg_turn();   //¾²Ì¬¶Ô»º´æ½âÎö
		cnt=0;
		process = IDEL;
		g.process_reg = TURN_PRO;
		g.process_cnt_change(INQ_turn);
		msg_reg.clear();
	}
}
void get_flop_info(char buff)
{
	int c=check_msg_end(buff);
	msg_reg.push_back(buff);
	if(c == FLOP_END)
	{
		catch_msg_flop();   //¾²Ì¬¶Ô»º´æ½âÎö
		cnt=0;
		process = IDEL;
		g.process_reg = FLOP_PRO;
		g.process_cnt_change(INQ_flop);
		msg_reg.clear();
	}
}
void get_river_info(char buff)
{
	int c=check_msg_end(buff);
	msg_reg.push_back(buff);
	if(c == RIVER_END)
	{
		catch_msg_river();   //¾²Ì¬¶Ô»º´æ½âÎö
		cnt=0;
		process = IDEL;
		g.process_reg = RIVER_PRO;
		g.process_cnt_change(INQ_river);
		msg_reg.clear();
	}
}
int get_info(char buff)
{
	if(process == GAMEOVER)
	{
		cout<<"GAMEOVER"<<endl;
		return GAMEOVER;
	}
	if(process==IDEL)
		check_msg_start(buff);
	else
	{
		switch(process)
		{
		case SEAT_PRO:
			{
				get_seat_info(buff);
				break;
			}
		case BLIND_PRO:
			{
				get_blind_info(buff);
				break;
			}
		case HOLD_PRO:
			{
				get_hold_info(buff);
				break;
			}
		case  INQ_PRO:
			{
				get_inq_info(buff);
				//send_msg(socket,CALL,0);
				break;
			}
		case  TURN_PRO:
			{

				get_turn_info(buff);
				//send_msg(socket,CALL,0);
				break;
			}
		case  FLOP_PRO:
			{

				get_flop_info(buff);
				//send_msg(socket,CALL,0);
				break;
			}
		case  RIVER_PRO:
			{

				get_river_info(buff);
				//send_msg(socket,CALL,0);
				break;
			}
		case POT_PRO:
			{
				g.clear_gamer();
				process = IDEL;
				g.process_reg = POT_PRO;
				g.foldcard_change(NOFOLD);
				msg_reg.clear();
				ac_time=3;
				break;
			} 
		
		default:  break;
		}

	}
	return PLAYING;
}


