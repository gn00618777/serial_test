#define MSG_HEADER_LEN	5
#define MAX_PACKET_LEN	231

enum {
	WATI_HEADER,
	WAIT_PAYLOAD,
}

int check_header(int *packet, int check_len) {

	int i;
	int tmp[check_len];

	for(i = 0 ; i < check_len ; i++) {
		if(*(packet + i) == 0xab && *(pcket + i + 1) == 0xba) {
			memcpy(tmp, packet + i, check_len - i);
			memcpy(packet, tmp, check_len - i);
			left = i;
		}

		//read one more byte to check whether the next
		//byte is 0xba or not
		if(i == check_len -1 && *(packet + i) == 0xab) {
			left = 1;
		}
	}

	return left;
}

int main() {

	int fd;
	int left = MSG_HEADER_LEN;
	int rcv_len;
	int rbuf[MAX_PACKET_LEN];
	int pos;
	int goal = MSG_HEADER_LEN;
	int status = WAIT_HEADER;

	fd = uart_init(); //non-blocking

	while(1) {

		FD_ZERO(&fdset);
		FD_SET(fd, &fdset);
		select(fd+1, &fdset, NULL, NULL, NULL);

		if(FS_ISSET(fd, &fdset)) {
			rcv_len = uart_read(packet + pos, rbuf, left);
			if(rcv_len > 0) {
				if(status = WAIT_HEADER) {
					pos += rcv_len;
					left -= rcv_len;
					if(pos == goal) {
						left = check_header(packet, pos);
						if(left == 0) {
							//go to next state
							status = WAIT_PAYLOAD;
							..
						} else {
							//still read byte
							goal = pos + left;
						}
					}
				} else if (status = WAIT_PAYLOAD) {
					...
				}
			}
		}

	}
}
