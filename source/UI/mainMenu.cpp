#include "gui.h"
#include "imgui.h"
#include "imgui_internal.h"
#include "appwindows.h"
#include "utils.h"
#include "localfiles.h"
#include "Enigma2.h"
#include "curldownloader.h"

#include "nxmp-i18n.h"

namespace Windows {
	
	
    void MainMenuWindow(bool *focus, bool *first_item) {
        Windows::SetupMainWindow();
		
		GUI::cloktimeText(ImVec2((1180.0f*multiplyRes)-ImGui::CalcTextSize(nxmpstats->currentTime).x-(10.0*multiplyRes),5.0f*multiplyRes),true,nxmpstats->currentTime);
		GUI::newbatteryIcon(ImVec2(1180.0f*multiplyRes,5.0f*multiplyRes),true,batteryPercent,40*multiplyRes,20*multiplyRes,true);
		
		if (ImGui::Begin(nxmpTitle.c_str(), nullptr, ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoCollapse)) {
			ImGui::PushStyleVar(ImGuiStyleVar_CellPadding, {0, 5});
			//ImGui::PushStyleColor(ImGuiCol_Header, ImVec4(0.26f, 0.59f, 0.98f, 0.00f));
			ImGui::PushStyleColor(ImGuiCol_HeaderHovered, NavHover_color);
			ImGui::PushStyleColor(ImGuiCol_NavHighlight, Active_color);
			
			if (ImGui::BeginTable("##table1", 2)){
				ImGui::TableSetupColumn("icon", ImGuiTableColumnFlags_WidthFixed, ((80.0f+ImGui::GetStyle().FramePadding.x) *multiplyRes -2 * ImGui::GetStyle().ItemSpacing.x)); 
				ImGui::TableSetupColumn("name", ImGuiTableColumnFlags_WidthStretch); 
				
				static int selected = -1;					
				for (unsigned int n = 0; n <  nxlangs::NX_MAINMENU_STR_NR_ITEMS; n++){
					ImGui::TableNextRow();
					std::string itemid = "##" + std::to_string(n);
					ImGui::TableSetColumnIndex(0);
					ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, ImVec2(ImGui::GetStyle().ItemSpacing.x, ImGui::GetStyle().CellPadding.y * 2)); // Fix
    				
					//if(n == MM_UPNP)ImGui::BeginDisabled();
					
					
					if(n == nxlangs::MM_LOCALFILES){
						GUI::NXMPImage((void*)(intptr_t)imgloader->icons.SdCardTexture.id, ImVec2(50,50));
					}
					else if(n == nxlangs::MM_USB){
						GUI::NXMPImage((void*)(intptr_t)imgloader->icons.UsbTexture.id, ImVec2(50,50));
					}
					else if(n == nxlangs::MM_NETWORK){
						GUI::NXMPImage((void*)(intptr_t)imgloader->icons.NetworkTexture.id, ImVec2(50,50));
					}
					else if(n == nxlangs::MM_UPNP){
						GUI::NXMPImage((void*)(intptr_t)imgloader->icons.UPNPTexture.id, ImVec2(50,50));
					}
					else if(n == nxlangs::MM_ENIGMA){
						GUI::NXMPImage((void*)(intptr_t)imgloader->icons.Enigma2Texture.id, ImVec2(50,50));
					}
					else if(n == nxlangs::MM_PLAYLIST){
						GUI::NXMPImage((void*)(intptr_t)imgloader->icons.PlaylistTexture.id, ImVec2(50,50));
					}
					else if(n == nxlangs::MM_STREAM){
						GUI::NXMPImage((void*)(intptr_t)imgloader->icons.NetworkTexture.id, ImVec2(50,50));
					}
					else if(n == nxlangs::MM_INFO){
						GUI::NXMPImage((void*)(intptr_t)imgloader->icons.InfoTexture.id, ImVec2(50,50));
					}
					else if(n == nxlangs::MM_SETTINGS){
						GUI::NXMPImage((void*)(intptr_t)imgloader->icons.SettingsTexture.id, ImVec2(50,50));
					}
					else if(n == nxlangs::MM_EXIT){
						GUI::NXMPImage((void*)(intptr_t)imgloader->icons.ExitTexture.id, ImVec2(50,50));
					}
					 
					ImGui::SameLine();
					ImGuiSelectableFlags selectable_flags = ImGuiSelectableFlags_SpanAllColumns;
							
					if (ImGui::Selectable(itemid.c_str(), selected == n,selectable_flags,ImVec2(1280*multiplyRes,50*multiplyRes))){
						if(n == nxlangs::MM_LOCALFILES){
							item.state = MENU_STATE_FILEBROWSER;
							filebrowser = new CFileBrowser(configini->getStartPath(),nullptr);
							filebrowser->setSordOrder((FS::FILESORTORDER)configini->getsortOrder(false));
							filebrowser->DirList(configini->getStartPath(),true,Utility::getMediaExtensions());
							item.first_item = true;
						}
						if(n == nxlangs::MM_USB){
							if(MyUSBMount==nullptr){
								if(!configini->getEmuOverrides()){
									MyUSBMount=new USBMounter(nullptr);
								}
							}
							item.state = MENU_STATE_USB_MOUNT;
							filebrowser = new CFileBrowser(MyUSBMount,nullptr);
							filebrowser->setSordOrder((FS::FILESORTORDER)configini->getsortOrder(false));
							
							
						}
						if(n == nxlangs::MM_NETWORK){
							item.networksources.clear();
							item.networksources = configini->getNetworks();
							item.state = MENU_STATE_NETWORKBROWSER;
							item.first_item = true;								
						}
						if(n == nxlangs::MM_UPNP){
							nxupnp = new NXUPnP();
							nxupnp->imgloader = imgloader;
							nxupnp->Discovery();
							item.state = MENU_STATE_UPNPBROWSER;
							item.first_item = true;
						}
						if(n == nxlangs::MM_ENIGMA){
							enigma2 = new Enigma2(configini->getEnigma());
							item.first_item = true;
							if(configini->getEnigma() == ""){
								item.state = MENU_STATE_ENIGMABROWSER;
							}else{
								enigma2->getServices();
								item.state = MENU_STATE_ENIGMABROWSER;
							}
						}
						if(n == nxlangs::MM_SETTINGS){
							if(sqlitedb != nullptr)sqlitedb->UpdateDbStats();
							item.state = MENU_STATE_SETTINGS;
							settingsview_open=true;
						}
						if(n == nxlangs::MM_PLAYLIST){
							item.state = MENU_STATE_PLAYLISTBROWSER;
							if(MediaProbe == nullptr){
								MediaProbe = new CMediaProbe(playlist);
								MediaProbe->StartMediaProbeThread();
							}
							
						}
						if(n == nxlangs::MM_INFO){
							item.state = MENU_STATE_INFO;
						}
						if(n == nxlangs::MM_EXIT){
							if(configini->getExitMode(false) == 0){
								item.state = MENU_STATE_APPEXIT;
							}else{
								renderloopdone = true;
							}
							
							//
						}
						if(n == nxlangs::MM_STREAM){
							//i need move this, work in progress.
							
							std::string namefile = "Streaming from Url...";
							std::string received = Utility::KeyboardCall ("Write the Url to start the streaming\n(Fembed, JKAnime, Bitly or Direct URL...)", tempKbUrl);
							
							tempKbUrl = received;
							curlDownloader Scraper;
							if (!received.compare("debug"))
							{
							}

							if (received.find("https://jk/") != std::string::npos)
							{
							Utility::replace(received,"https://jk/","https://jkanime.net/");
							
							}
							if (received.find("https://bit.ly/") != std::string::npos)
							{//if the response from the address does not arrive within 5 seconds, it sends the direct link.
							received = Scraper.getRedirection(received,"",false,"",false);
							}

							if (received.find("https://jkanime.net/") != std::string::npos)
							{
							namefile = "Streaming from JKAnime...";
							received = Utility::Nozomi_Link(received);
							}

							if(received.find("http") != std::string::npos)
							{
							std::cout << "This: "<< received.c_str() << std::endl;
							libmpv->loadFileLive(received,namefile.c_str());
							}
						//i need move this, work in progress.
						}


					}
							
															
					ImGui::TableSetColumnIndex(1);
					
					ImGui::SetCursorPos({ImGui::GetCursorPos().x, ImGui::GetCursorPos().y + ((50*multiplyRes) - ImGui::GetFont()->FontSize) / 2});
					
					
					
					
					
					//ImGui::SetCursorPos({ImGui::GetCursorPos().x, ImGui::GetCursorPos().y + ((50*multiplyRes) - ImGui::GetFont()->FontSize) / 2});
					
					ImGui::Text("%s",nxlangs::get_mainmenu_str((nxlangs::NX_MAINMENU_STR)n).c_str());
					ImGui::PopStyleVar();
					
					//if(n == MM_UPNP)ImGui::EndDisabled();
					
				}
				
				if (*first_item) {
					std::string itemid = "##" + std::to_string(0);
					ImGui::SetFocusID(ImGui::GetID(itemid.c_str()), ImGui::GetCurrentWindow());
					ImGuiContext& g = *ImGui::GetCurrentContext();
					g.NavDisableHighlight = false;
					g.NavDisableMouseHover = true;
					*first_item = false;
				}
				ImGui::EndTable();
				ImGui::PopStyleVar();
				ImGui::PopStyleColor(2);
			}	
		}
		
		Windows::ExitMainWindow();
		
	}
}
		