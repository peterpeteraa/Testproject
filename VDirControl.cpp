/*	系統	*/
#ifndef WIN32
#  include <dirent.h>
#  include <ctype.h>
#  include <sys/stat.h>
#  include <sys/uio.h>
#  include <sys/types.h>
#  include <string.h>
#  include <unistd.h>
#  include <sys/uio.h>
#  include <stdio.h>
#  include <sys/vfs.h>
#  include <sys/statvfs.h>
#  include <fcntl.h>
#else
#  include <string.h>
#  include <stdio.h>
#  include <direct.h>
#  include <io.h>
#  include <windows.h>
#endif

/*	自訂	*/
#include "VDirControl.h"
#include "generaldef.h"

#ifndef WIN32

int vfopen(const char* path, int flags)
{
	int fd = -1;
	fd = open(path, flags);
	if(fd<0)
	{ 
		DEBUG_PRINT_USER( fprintf(stderr,"%s:can't open %s\n",__func__,path) );
	}
	
	return fd;
}

int vfclose(int fd)
{
	return close(fd);
}


long long vftell(int fd)
{
	if (fd <= 0)
	{
		ERR_PRINT("no device\n");
		return -1;
	}
	long long nOffset = lseek64(fd, 0, SEEK_END);
	if (nOffset < 0)
	{
		ERR_PRINT("lseek64 error\n");
	}
	
	return nOffset;
}

long long vfread(void* buffer,long long size, long long count,int fd)
{
	if(fd <= 0)
	{
		ERR_PRINT("error fd\n");
		return -1;
	}

	long long nReadLen = read(fd, buffer, size * count);
	
	if(nReadLen<0)
	{
		ERR_PRINT("error of read function\n");
		perror("read:");
	}
	else if (nReadLen != size * count)
	{
		DEBUG_PRINT_USER( fprintf(stderr,"%s: nReadLen=%lld , size * count=%lld \n",__func__, nReadLen, size * count) );
	}
	
	return nReadLen;
}

long long vfwrite(void* buffer,long long size, long long count,int fd)
{
	if(fd <= 0)
	{
		ERR_PRINT("error fd\n");
		return -1;
	}

	long long nReadLen = write(fd, buffer, size * count);
	
	if(nReadLen<0)
	{
		ERR_PRINT(" error of read function \n");
		perror("write:");
	}
	else if (nReadLen != size * count)
	{
		DEBUG_PRINT_USER( fprintf(stderr,"%s: nReadLen=%lld , size * count=%lld \n",__func__,nReadLen, size * count) );
	}
	
	return nReadLen;
}

#endif
