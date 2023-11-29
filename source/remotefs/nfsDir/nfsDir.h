#ifndef NXMP_NFSDIR_H
#define NXMP_NFSDIR_H

#include <string>
#include <vector>
#include <stdio.h>
#include <cstring>
#include "localfiles.h"
#include "playlist.h"

class nfsDir{
public:
	nfsDir(std::string _url,Playlist * _playlist);
	
	bool DirList(std::string path,bool showHidden,const std::vector<std::string> &extensions);
	std::vector<FS::FileEntry> getCurrList();
	
	std::string backDir();
	std::string getUrl();
	std::string getCurrPath();
	std::string getBasePath();
	
	bool *checked(int pos);
	void clearChecked();
	
	int sortOrder=0;
	
	void SetFileDbStatus(int idx,int dbstatus);
	void ResetDbStatus();
	
	std::string errormsg = "";
	
private:
	std::vector<FS::FileEntry> currentlist;
	std::string url;
	std::string basepath = "";
	std::string currentpath = "";
	Playlist *playlist;
	
};

#endif