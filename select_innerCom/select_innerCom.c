typedef unsigned char UINT8  



UINT16 CRC16_CalculateBuf(UINT16 *ptr, int len){
	
	
	return UINT16;
}

void antenna_enable(UINT8 enabe){
	int sendcnt, txindex, leftcnt, txcnt = 0;	
	UINT8 org_buff[10];


	org_buff[0] = 0x55;
	org_buff[1] = 0x00;
	org_buff[2] = 0x04;
	org_buff[3] = 0x63;
	org_buff[4] = 0x36;
	org_buff[5] = 0x1;
	org_buff[6] = enabe;

	CRC_value = CRC16_CalculateBuf($org_buff[1], 6);

	org_buff[7] = 0x55;
	org_buff[8] = 0x55;

	txcnt = 9;
	sendcnt = txcnt;
	leftcnt = txcnt;
	txindex = 0;	

	while(leftcnt > 0)
	{
		sendcnt = write(fd, &org_buff[txindex], sendcnt);
		if(sendcnt<0){
			break;
		}

		txindex += sendcnt;
		leftcnt -= sendcnt;
		if(leftcnt < 9){
			sendcnt = leftcnt;
		}else{
			sendcnt = 9;
		}
	}
}



int main(int argc, const char *argv[])
{
	fd_set temp_fds, cominner_fds;
	int fd;

	FD_ZERO(&cominner_fds);
	FD_SET(fd, &cominner_fds);

	ret  = select(50, &temp_fds, NULL, NULL, NULL);
	if(ret < 0){
		continue;
	}

	while(1) 
	{	
		if(FD_ISSET(fd, cominner_fds)){
			if(fd == fd_com_inner){
				ioctl(fd, FIONREAD, &nread);
				com_inner_cmdprocess(fd_com_inner, nread);
			}
		}
	}
	return 0;
}
