#include <stdio.h>
#include <dirent.h>//for using dirent structure
#include <sys/stat.h> // for using stat structure, S_ISDIR, S_ISREG
#include <sys/types.h>
#include <unistd.h>
#include <time.h>



int main(){
	DIR* dp = NULL;
	struct dirent* entry = NULL;
	struct stat buf;
	struct tm* mtime;

	if((dp=opendir(".")) == NULL){
		printf("디렉토리를 열기에 실패했습니다\n");
		return -1;
	}
	else{
//		printf("success open directory");
	}

	while((entry = readdir(dp)) != NULL){
		lstat(entry ->d_name,&buf);//get more specific info abt the file
		mtime = localtime(&buf.st_mtime);
		
		if(S_ISDIR(buf.st_mode))
			printf("[dir] %10s",entry -> d_name);
		else if(S_ISREG(buf.st_mode))
			printf("[reg] %10s",entry ->d_name);
		
		printf("\tuid = %d, gid=%d, %ld bytes, mtime=",buf.st_uid,buf.st_gid,buf.st_size);
//		printf("last file modification : %s\n",ctime(buf.st_mtime));
printf("%d:%d:%d %d:%d:%d\n",mtime->tm_year+1900, mtime->tm_mon+1,mtime->tm_mday, mtime->tm_hour,mtime->tm_min,mtime->tm_sec);
	}

closedir(dp);
}







