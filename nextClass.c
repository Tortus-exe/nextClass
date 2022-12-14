#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char* argv[]) {
	FILE* p;
	char *out = NULL;
	int h,m,time,classTime;
	size_t outlen = 0;

	p = popen("date \"+%H:%M\"", "r");
	getline(&out, &outlen, p);
	pclose(p);
	sscanf(out, "%d:%d", &h,&m);
	time = (h*60)+m;

	p = popen("calcurse -Q", "r");
	getline(&out, &outlen, p);	//consume one line
	while(getline(&out, &outlen, p) >= 0) {
		sscanf(out, " - %d:%d%*s\n", &h, &m);
		classTime = (h*60)+m;
		getline(&out, &outlen, p);
		if(time < classTime) {
			printf("(%d:%02d) %s", h,m,(out+1));
			break;
		}
	}

	pclose(p);
	free(out);
	return 0;
}
