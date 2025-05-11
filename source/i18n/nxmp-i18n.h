#pragma once

#ifndef NXMP_I18N_H
#define NXMP_I18N_H

#include <stdio.h>
#include <string.h>
#include <cstdlib>

#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <dirent.h>
#include <string>
#include <vector>
#include <jansson.h>
#include <switch.h>

namespace nxlangs{
	
	enum NX_MAINMENU_STR{
		MM_LOCALFILES,
		MM_USB,
		MM_STREAM,
		MM_NETWORK,
		MM_UPNP,
		MM_ENIGMA,
		MM_PLAYLIST,
		MM_SETTINGS,
		MM_INFO,
		MM_EXIT,
		NX_MAINMENU_STR_NR_ITEMS
	};

	enum NX_COMMON_STR{
		NXCOMMON_YES,
		NXCOMMON_NO,
		NXCOMMON_OK,
		NXCOMMON_AUTO,
		NXCOMMON_NAVIGATION,
		NXCOMMON_SELECT,
		NXCOMMON_SELECTPLAY,
		NXCOMMON_HOME,
		NXCOMMON_HOMESAVE,
		NXCOMMON_BACK,
		NXCOMMON_CONTEXTMENU,
		NXCOMMON_NAME,
		NXCOMMON_SIZE,
		NXCOMMON_DATE,
		NXCOMMON_MOVEUP,
		NXCOMMON_MOVEDOWN,
		NXCOMMON_DELETE,
		NXCOMMON_EXIT,
		NXCOMMON_CANCEL,
		NXCOMMON_SAVE,
		NXCOMMON_CHECKBOX,
		
		NX_COMMON_STR_NR_ITEMS
	};

	enum NX_POPUP_STR{
		NXPOPUP_SAVESETTINGS,
		NXPOPUP_RESUMEPLAY,
		NXPOPUP_DBUPDATED,
		NXPOPUP_DBWASUPDATED,
		NXPOPUP_NETWORKPOPUP,
		NXPOPUP_FILEMENU,
		NXPOPUP_SORTASC_NAME,
		NXPOPUP_SORTASC_SIZE,
		NXPOPUP_SORTASC_DATE,
		NXPOPUP_SORTDESC_NAME,
		NXPOPUP_SORTDESC_SIZE,
		NXPOPUP_SORTDESC_DATE,
		NXPOPUP_ADDFILEPLAYLIST,
		NXPOPUP_ADDSELEPLAYLIST,
		NXPOPUP_REMOVEELEMENT,
		NXPOPUP_CLEARPLAYLIST,
		NXPOPUP_SETASSTARTING,
		
		NX_POPUP_STR_NR_ITEMS
	};


	enum NX_SETTINGS_STR{
		/* GENERAL TAB */
		NXSET_GENERALS,
		NXSET_FILEBROWSER,
		NXSET_HIDDENFILES,
		NXSET_NAVIGATION,
		NXSET_TOUCHCONTROL,
		NXSET_OVERCLOCK,
		NXSET_OVERCLOCK_STARTUP,
		NXSET_MISC,
		NXSET_VSYNC,
		NXSET_INTLANG,
		/* PLAYER SETTINGS TAB */
		NXSET_PLAYERSETTINGS,
		NXSET_DECODER,
		NXSET_HWDECODER,
		NXSET_DEMUXCACHE,
		NXSET_DEMUXCACHESEC,
		NXSET_AUDIO,
		NXSET_AUDIOOUTPUT,
		NXSET_SEEK,
		NXSET_SHORTSEEK,
		NXSET_LONGSEEK,
		NXSET_LANG,
		NXSET_USEALANG,
		NXSET_ALANG,
		NXSET_USESLANG,
		NXSET_SLANG,
		NXSET_SUBTITLE,
		NXSET_SUBFONTSIZE,
		NXSET_SUBFONTSCALE,
		NXSET_VIDEO,
		NXSET_VIDEODEINT,
		/* DATABASE TAB */
		NXSET_DATABASE,
		NXSET_USEDATABASE,
		NXSET_DATABASEVERSION,
		NXSET_SQLITEVERSION,
		NXSET_RESUMEPOINTCOUNT,
		NXSET_COMPLETEDCOUNT,
		NXSET_DATABASENOTACTIVE,
		NXSET_STARTSAVINGINFO,
		NXSET_STOPSAVINGINFO,
		/* TOUCH SETTINGS TAB */
		NXSET_TOUCHSETTINGS,
		
		NX_SETTINGS_STR_NR_ITEMS
	};


	enum NX_NETWORK_STR{
		NXNET_ADDSHARE,
		NXNET_ADDSHAREMENU,
		NXNET_SHARECONFIG,
		NXNET_SHARENAME,
		NXNET_PROTOCOL,
		NXNET_CREDENTIALS,
		NXNET_ADDRESS,
		NXNET_PORT,
		NXNET_USERNAME,
		NXNET_PASSWORD,
		NXNET_ANONYMOUS,
		NXNET_REMOTEPATH,
		NXNET_REMOTEPATHDESC,
		NXNET_REMOTESHAREDESC,
		NXNET_TESTCONNECTION,
		NXNET_TESTOK,
		NXNET_TESTERROR,
		NXNET_NETWORKSOURCESEL,
		NXNET_NETWORKSOURCEMENU,
		
		
		NX_NETWORK_STR_NR_ITEMS
	};
	
	
	
	
	typedef struct {
		int id = 0;
		std::string name = "";
		std::string author = "";
		std::string filepath = "";
		bool native = false;
		bool status = false;
		std::vector<std::string> mainmenu;
		std::vector<std::string> common;
		std::vector<std::string> popup;
		std::vector<std::string> settingsmenu;
		std::vector<std::string> network;
		
	} lang_struct;
	
	
	extern std::vector<lang_struct> langslist;
	extern std::vector<std::string> langfileslist;
	
	extern unsigned int selectedlang;
	
	extern std::string get_mainmenu_str(NX_MAINMENU_STR strval);
	
	extern std::string get_common_str(NX_COMMON_STR strval);
	
	extern std::string get_popup_str(NX_POPUP_STR strval);
	
	extern std::string get_settingsmenu_str(NX_SETTINGS_STR strval);
	
	extern std::string get_network_str(NX_NETWORK_STR strval);
	
	void Init_Langs();
	
	
	//void InitLang(NX_LANGS mylang);
	void FetchUserLangs(std::string _path);
	void DestroyLang();
	
	extern std::string GetCurrentLangName();
	
}




#endif