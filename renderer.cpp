#include "includes.hpp"
#include "utils.hpp"
#include "fixedsys.hpp"
#include "ImGuiPP.h"
#include "fontawesome.h"

static ID3D11Device           * g_pd3dDevice           = nullptr;
static ID3D11DeviceContext    * g_pd3dDeviceContext    = nullptr;
static IDXGISwapChain         * g_pSwapChain           = nullptr;
static ID3D11RenderTargetView * g_mainRenderTargetView = nullptr;

bool CreateDeviceD3D( HWND );
void CleanupDeviceD3D( );
void CreateRenderTarget( );
void CleanupRenderTarget( );
LRESULT __stdcall WndProc( HWND, UINT , WPARAM, LPARAM );

char PassWordEmail[20] = "";
char UserName[20] = "";
char RgPassWord[20] = "";
char RgUserName[20] = "";
char license[20] = "";
char licensenew[20] = "";

void colors()
{
    ImGuiStyle& style = ImGui::GetStyle();
    auto color = style.Colors;

    style.WindowMinSize = ImVec2(555, 288);
    style.FramePadding = ImVec2(0, 0);
    style.WindowPadding = ImVec2(0, 0);

    style.FrameRounding = 3;

    color[ImGuiCol_FrameBg] = ImColor(35, 35, 35);
    color[ImGuiCol_FrameBgActive] = ImColor(35, 35, 35);
    color[ImGuiCol_FrameBgHovered] = ImColor(35, 35, 35);

    color[ImGuiCol_Button] = ImColor(35, 35, 35);
    color[ImGuiCol_ButtonActive] = ImColor(65, 65, 65);
    color[ImGuiCol_ButtonHovered] = ImColor(60, 60, 60);

    color[ImGuiCol_Border] = ImColor(10, 10, 10);
    color[ImGuiCol_WindowBg] = ImColor(10, 10, 10);

    color[ImGuiCol_ChildBg] = ImColor(10, 10, 10);

    //color[ImGuiCol_ChildBg] = ImColor(10, 10, 10);
}

struct Globals3
{
    static Globals3* Get()
    {
        static auto* instance = new Globals3();
        return instance;
    }
    int MenuTab = 0;
    float Speed = 0;
    bool Godmode = false;
    bool Darkmode = true;
};
static auto G = Globals3::Get();

int StartRendering( ) 
{   
    const auto title = utils::random_string( );
    utils::spoof_exe( false );

    WNDCLASSEX wc = 
    { 
        sizeof( WNDCLASSEX ),
        CS_CLASSDC,
        WndProc, 
        0, 
        0, 
        0, 
        0, 
        0, 
        0, 
        0, 
        title.c_str(),
        0
    };

    RegisterClassExA( &wc );
    HWND hwnd = CreateWindowExA(0, wc.lpszClassName , title.c_str() , WS_SYSMENU , 100 , 100 , 1280 , 800 , 0 , 0 , wc.hInstance , 0 );

    if ( !CreateDeviceD3D( hwnd ) )
    {
        CleanupDeviceD3D( );
        UnregisterClassA( wc.lpszClassName , wc.hInstance );

        return 1;
    }

    ShowWindow( GetConsoleWindow( ) , SW_HIDE );
    ShowWindow( hwnd , SW_SHOWDEFAULT );
    UpdateWindow( hwnd );

    //ImGui::GetIO().Fonts->AddFontFromMemoryTTF(const_cast<std::uint8_t*>(fixedsys), sizeof(fixedsys), 18);

    ImGui::CreateContext( );

    ImGuiIO& io = ImGui::GetIO( ); 

    io.IniFilename = nullptr;
    io.LogFilename = nullptr;

    io.WantSaveIniSettings = false;

    //ImGui::StyleColorsDark( );

    static const ImWchar icons_ranges[] = { 0xf000, 0xf3ff, 0 };
    ImFontConfig icons_config;

    icons_config.MergeMode = true;
    icons_config.PixelSnapH = true;
    icons_config.OversampleH = 2.5;
    icons_config.OversampleV = 2.5;
    ImFontConfig CustomFont;

    ImGui::GetIO().Fonts->AddFontFromMemoryTTF(const_cast<std::uint8_t*>(fixedsys), sizeof(fixedsys), 18);
    ImGui::GetIO().Fonts->AddFontFromMemoryCompressedTTF(font_awesome_data, font_awesome_size, 23.f, &icons_config, icons_ranges);
    ImFont* font1 = io.Fonts->AddFontFromFileTTF("C:\\Windows\\Fonts\\Bahnschrift.ttf", 40);
    ImFont* font2 = io.Fonts->AddFontFromFileTTF("C:\\Windows\\Fonts\\Bahnschrift.ttf", 16.5);

    ImGui_ImplWin32_Init( hwnd );
    ImGui_ImplDX11_Init( g_pd3dDevice , g_pd3dDeviceContext );

    const auto clear_color = ImVec4( 0.45f , 0.55f , 0.60f , 1.00f );
    const float clear_color_with_alpha[4] = { clear_color.x * clear_color.w, clear_color.y * clear_color.w, clear_color.z * clear_color.w, clear_color.w };

    while ( true )
    {
        MSG msg;

        while ( PeekMessageA( &msg , NULL , 0U , 0U , PM_REMOVE ) )
        {
            TranslateMessage( &msg );
            DispatchMessageA( &msg );

            if ( msg.message == WM_QUIT )
                break;
        }

        ImGui_ImplDX11_NewFrame( );
        ImGui_ImplWin32_NewFrame( );
        ImGui::NewFrame( );

        colors();

        {
            float wysokoaa_distance = 16;  //höhe

            float szerokoaad_distance = 160;
            float szerokoaaddd_distance = -6;

            static int currentColumn = 1;
            switch (currentColumn)
            {
            case 1:
            if (ImGui::Begin( "ghosted.vip ##login", 0, ImGuiWindowFlags_NoResize || ImGuiWindowFlags_NoTitleBar || ImGuiWindowFlags_NoScrollbar || ImGuiWindowFlags_NoCollapse ) ) {

                ImGui::SetCursorPosY(ImGui::GetCursorPosY() + wysokoaa_distance);
                ImGui::SetCursorPosX(ImGui::GetCursorPosX() + szerokoaad_distance);
                ImGui::PushFont(font1);
                ImGui::Text("ghosted", 0, false);
                ImGui::SameLine();
                ImGui::SetCursorPosX(ImGui::GetCursorPosX() + szerokoaaddd_distance);
                ImGui::PushStyleColor(ImGuiCol_Text, IM_COL32(183, 0, 255, 255));
                ImGui::Text(".vip");
                ImGui::PopStyleColor();
                ImGui::PopFont();
                ImGui::Spacing();
                ImGui::Spacing();
                ImGui::Spacing();
                ImGui::Spacing();
                ImGui::Spacing();
                ImGui::Spacing();
                ImGui::Spacing();
                ImGui::Spacing();
                ImGui::Spacing();
                ImGui::Spacing();

                ImGui::PushFont(font2);
                ImGui::SetCursorPosX(ImGui::GetCursorPosX() + 140);
                ImGui::Text("Username:");
                ImGui::SetCursorPosX(ImGui::GetCursorPosX() + 140);
                ImGui::InputTextEx("##username", NULL, UserName, IM_ARRAYSIZE(UserName), ImVec2(240, 28), 0, 0);
                ImGui::SetCursorPosX(ImGui::GetCursorPosX() + 140);
                ImGui::Text("Password:");
                ImGui::SetCursorPosX(ImGui::GetCursorPosX() + 140);
                //ImGui::InputTextEx("##password", PassWordEmail, IM_ARRAYSIZE(PassWordEmail), ImVec2(240, 28), 0, 0);
                ImGui::InputTextEx("##license", NULL, PassWordEmail, IM_ARRAYSIZE(PassWordEmail), ImVec2(240, 28), 0, 0);
                ImGui::PopFont();
                ImGui::Spacing();
                ImGui::Spacing();
                ImGui::Spacing();
                ImGui::Spacing();
                ImGui::Spacing();
                ImGui::Spacing();
                ImGui::SetCursorPosX(ImGui::GetCursorPosX() + 140);
                ImGui::SetCursorPosY(ImGui::GetCursorPosY() + -20);
                if (ImGui::Button("Login", ImVec2(65, 32)))
                {
                    currentColumn = 2;
                }
                ImGui::SameLine();
                if (ImGui::Button("Register", ImVec2(70, 32)))
                {
                    currentColumn = 3;
                }
                ImGui::End();
                break;
              }
              
            case 2:
                if (ImGui::Begin("ghosted.vip ##main", 0, ImGuiWindowFlags_NoResize || ImGuiWindowFlags_NoTitleBar || ImGuiWindowFlags_NoScrollbar || ImGuiWindowFlags_NoCollapse))
                {
                    ImGui::PushStyleColor(ImGuiCol_Border, ImColor(10, 10, 10).Value);
                    ImGui::PushStyleColor(ImGuiCol_ChildBg, ImColor(11, 11, 11).Value);
                    ImGui::BeginChild("##LeftSideBar", ImVec2(50, ImGui::GetContentRegionAvail().y), true, ImGuiWindowFlags_NoResize);
                    {
                        auto fakebuttonfromwish = [](const char* name, int newTab)
                        {
                            //bool hovereds, helds;
                            //const ImU32 col = ImGui::GetColorU32((helds && hovereds) ? ImGuiCol_ButtonActive : hovereds ? ImGuiCol_ButtonHovered : ImGuiCol_Button);

                            ImGui::NewLine();
                            ImGui::SetCursorPosX(ImGui::GetCursorPosX() + 18);
                            ImGui::PushStyleColor(ImGuiCol_Text, G->MenuTab == newTab ? IM_COL32(255, 255, 255, 255) : IM_COL32(120, 120, 120, 255));
                            if (G->MenuTab == newTab)
                            {

                                ImGui::SetCursorPosX(0);
                                ImGui::Text("");
                                ImGui::SameLine(0, 200 / 10.6);
                            }
                            ImGui::Text(name);
                            ImGui::PopStyleColor();
                            if (ImGui::IsItemClicked())
                                G->MenuTab = newTab;
                        };

                        fakebuttonfromwish(ICON_FA_TERMINAL, 0);
                        ImGui::SetCursorPosY(ImGui::GetCursorPosY() + -15);
                        fakebuttonfromwish(ICON_FA_USER, 1);
                        fakebuttonfromwish(ICON_FA_PLUS, 2);
                    }
                    ImGui::EndChild();
                    ImGui::PopStyleColor(2);

                    {
                        ImGui::PushStyleColor(ImGuiCol_Separator, ImColor(21, 21, 21).Value);
                        ImGui::SameLine(0);
                        ImGui::SeparatorEx(ImGuiSeparatorFlags_Vertical);
                        ImGui::SameLine();
                        ImGui::PopStyleColor();
                    }


                    ImGui::BeginChild("##RightSide", ImVec2(ImGuiPP::GetX(), ImGuiPP::GetY()), TRUE);
                    {
                        if (G->MenuTab == 0)
                        {
                            ImGui::SetCursorPosY(ImGui::GetCursorPosY() + wysokoaa_distance + -12);
                            ImGui::SetCursorPosX(ImGui::GetCursorPosX() + szerokoaad_distance + 135);
                            ImGui::PushFont(font1);
                            ImGui::Text("ghosted", 0, false);
                            ImGui::SameLine();
                            ImGui::SetCursorPosX(ImGui::GetCursorPosX() + szerokoaaddd_distance);
                            ImGui::PushStyleColor(ImGuiCol_Text, IM_COL32(21, 193, 212, 255));
                            ImGui::Text(".vip");
                            ImGui::PopStyleColor();
                            ImGui::PopFont();

                            {
                                ImGui::PushStyleColor(ImGuiCol_Separator, ImColor(21, 21, 21).Value);
                                ImGui::SeparatorEx(ImGuiSeparatorFlags_Horizontal);
                                ImGui::PopStyleColor();
                            }

                        }
                        else if (G->MenuTab == 1)
                        {
                            
                            ImGui::SetCursorPosY(ImGui::GetCursorPosY() + wysokoaa_distance + -12);
                            ImGui::SetCursorPosX(ImGui::GetCursorPosX() + szerokoaad_distance + 135);
                            ImGui::PushFont(font1);
                            ImGui::Text("ghosted", 0, false);
                            ImGui::SameLine();
                            ImGui::SetCursorPosX(ImGui::GetCursorPosX() + szerokoaaddd_distance);
                            ImGui::PushStyleColor(ImGuiCol_Text, IM_COL32(183, 0, 255, 255));
                            ImGui::Text(".vip");
                            ImGui::PopStyleColor();
                            ImGui::PopFont();

                            {
                                ImGui::PushStyleColor(ImGuiCol_Separator, ImColor(21, 21, 21).Value);
                                ImGui::SeparatorEx(ImGuiSeparatorFlags_Horizontal);
                                ImGui::PopStyleColor();
                            }

                        }
                        else if (G->MenuTab == 2)
                        {
                            ImGui::SetCursorPosY(ImGui::GetCursorPosY() + wysokoaa_distance + -12);
                            ImGui::SetCursorPosX(ImGui::GetCursorPosX() + szerokoaad_distance + 135);
                            ImGui::PushFont(font1);
                            ImGui::Text("ghosted", 0, false);
                            ImGui::SameLine();
                            ImGui::SetCursorPosX(ImGui::GetCursorPosX() + szerokoaaddd_distance);
                            ImGui::PushStyleColor(ImGuiCol_Text, IM_COL32(183, 0, 255, 255));
                            ImGui::Text(".vip");
                            ImGui::PopStyleColor();
                            ImGui::PopFont();

                            {
                            ImGui::PushStyleColor(ImGuiCol_Separator, ImColor(21, 21, 21).Value);
                            ImGui::SeparatorEx(ImGuiSeparatorFlags_Horizontal);
                            ImGui::PopStyleColor();
                            }

                            ImGui::PushFont(font2);
                            ImGui::SetCursorPosY(ImGui::GetCursorPosY() + -10);
                            ImGui::SetCursorPosX(ImGui::GetCursorPosX() + 1);
                            ImGui::Text("Username:");
                            ImGui::SetCursorPosX(ImGui::GetCursorPosX() + 1);
                            ImGui::InputTextEx("##username", NULL, UserName, IM_ARRAYSIZE(UserName), ImVec2(240, 28), 0, 0);
                            ImGui::SetCursorPosX(ImGui::GetCursorPosX() + 1);
                            ImGui::Text("License:");
                            ImGui::SetCursorPosX(ImGui::GetCursorPosX() + 1);
                            ImGui::InputTextEx("##licens", NULL, licensenew, IM_ARRAYSIZE(licensenew), ImVec2(240, 28), 0, 0);
                            ImGui::PopFont();
                            ImGui::SetCursorPosX(ImGui::GetCursorPosX() + 1);
                            ImGui::SetCursorPosY(ImGui::GetCursorPosY() + 1);
                            if (ImGui::Button("add", ImVec2(65, 32)))
                            {
                                
                            }
                        }
                    }
                    ImGui::EndChild();
                }
                ImGui::End();
                break;

            case 3:
                if (ImGui::Begin("ghosted.vip ##Register", 0, ImGuiWindowFlags_NoResize || ImGuiWindowFlags_NoTitleBar || ImGuiWindowFlags_NoScrollbar || ImGuiWindowFlags_NoCollapse))
                {
                    ImGui::SetCursorPosY(ImGui::GetCursorPosY() + wysokoaa_distance);
                    ImGui::SetCursorPosX(ImGui::GetCursorPosX() + szerokoaad_distance);
                    ImGui::PushFont(font1);
                    ImGui::Text("ghosted", 0, false);
                    ImGui::SameLine();
                    ImGui::SetCursorPosX(ImGui::GetCursorPosX() + szerokoaaddd_distance);
                    ImGui::PushStyleColor(ImGuiCol_Text, IM_COL32(183, 0, 255, 255));
                    ImGui::Text(".vip");
                    ImGui::PopStyleColor();
                    ImGui::PopFont();
                    ImGui::Spacing();
                    ImGui::Spacing();
                    ImGui::Spacing();
                    ImGui::Spacing();
                    ImGui::Spacing();
                    ImGui::Spacing();
                    ImGui::Spacing();
                    ImGui::Spacing();
                    ImGui::Spacing();
                    ImGui::Spacing();

                    ImGui::PushFont(font2);
                    ImGui::SetCursorPosY(ImGui::GetCursorPosY() + -10);
                    ImGui::SetCursorPosX(ImGui::GetCursorPosX() + 140);
                    ImGui::Text("Username:");
                    ImGui::SetCursorPosX(ImGui::GetCursorPosX() + 140);
                    ImGui::InputTextEx("##username", NULL, UserName, IM_ARRAYSIZE(UserName), ImVec2(240, 28), 0, 0);
                    ImGui::SetCursorPosX(ImGui::GetCursorPosX() + 140);
                    ImGui::Text("Password:");
                    ImGui::SetCursorPosX(ImGui::GetCursorPosX() + 140);
                    //ImGui::InputTextEx("##password", PassWordEmail, IM_ARRAYSIZE(PassWordEmail), ImVec2(240, 28), 0, 0);
                    ImGui::InputTextEx("##license", NULL, PassWordEmail, IM_ARRAYSIZE(PassWordEmail), ImVec2(240, 28), 0, 0);
                    ImGui::SetCursorPosX(ImGui::GetCursorPosX() + 140);
                    ImGui::Text("License:");
                    ImGui::SetCursorPosX(ImGui::GetCursorPosX() + 140);
                    ImGui::InputTextEx("##licens", NULL, license, IM_ARRAYSIZE(license), ImVec2(240, 28), 0, 0);
                    ImGui::PopFont();
                    ImGui::Spacing();
                    ImGui::Spacing();
                    ImGui::Spacing();
                    ImGui::Spacing();
                    ImGui::Spacing();
                    ImGui::Spacing();
                    ImGui::SetCursorPosX(ImGui::GetCursorPosX() + 140);
                    ImGui::SetCursorPosY(ImGui::GetCursorPosY() + -20);
                    if (ImGui::Button("Register", ImVec2(70, 32)))
                    {
                        currentColumn = 2;
                    }
                    ImGui::SameLine();
                    if (ImGui::Button("go back", ImVec2(65, 32)))
                    {
                        currentColumn = 1;
                    }
                    ImGui::End();
                }
                break;
            }



        }

        ImGui::Render( );
       
        g_pd3dDeviceContext->OMSetRenderTargets( 1 , &g_mainRenderTargetView , NULL );
        g_pd3dDeviceContext->ClearRenderTargetView( g_mainRenderTargetView , clear_color_with_alpha );
       
        ImGui_ImplDX11_RenderDrawData( ImGui::GetDrawData( ) );

        g_pSwapChain->Present(0, 0); 
    }

    ImGui_ImplDX11_Shutdown( );
    ImGui_ImplWin32_Shutdown( );
    ImGui::DestroyContext( );

    CleanupDeviceD3D( );
    DestroyWindow( hwnd );
    UnregisterClassA( wc.lpszClassName , wc.hInstance );

    return 0;
}


bool CreateDeviceD3D( HWND hWnd )
{
    DXGI_SWAP_CHAIN_DESC sd;
    ZeroMemory( &sd , sizeof( sd ) );
    sd.BufferCount = 2;
    sd.BufferDesc.Width = 0;
    sd.BufferDesc.Height = 0;
    sd.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
    sd.BufferDesc.RefreshRate.Numerator = 60;
    sd.BufferDesc.RefreshRate.Denominator = 1;
    sd.Flags = DXGI_SWAP_CHAIN_FLAG_ALLOW_MODE_SWITCH;
    sd.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
    sd.OutputWindow = hWnd;
    sd.SampleDesc.Count = 1;
    sd.SampleDesc.Quality = 0;
    sd.Windowed = TRUE;
    sd.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;

    UINT createDeviceFlags = 0;

    D3D_FEATURE_LEVEL featureLevel;
    const D3D_FEATURE_LEVEL featureLevelArray[2] = { D3D_FEATURE_LEVEL_11_0, D3D_FEATURE_LEVEL_10_0, };

    if ( D3D11CreateDeviceAndSwapChain( NULL , D3D_DRIVER_TYPE_HARDWARE , NULL , createDeviceFlags , featureLevelArray , 2 , D3D11_SDK_VERSION , &sd , &g_pSwapChain , &g_pd3dDevice , &featureLevel , &g_pd3dDeviceContext ) != S_OK )
        return false;

    CreateRenderTarget( );
    return true;
}

void CleanupDeviceD3D( )
{
    CleanupRenderTarget( );
    if ( g_pSwapChain ) { g_pSwapChain->Release( ); g_pSwapChain = NULL; }
    if ( g_pd3dDeviceContext ) { g_pd3dDeviceContext->Release( ); g_pd3dDeviceContext = NULL; }
    if ( g_pd3dDevice ) { g_pd3dDevice->Release( ); g_pd3dDevice = NULL; }
}

void CreateRenderTarget( )
{
    ID3D11Texture2D* pBackBuffer;
    g_pSwapChain->GetBuffer( 0 , IID_PPV_ARGS( &pBackBuffer ) );
    g_pd3dDevice->CreateRenderTargetView( pBackBuffer , NULL , &g_mainRenderTargetView );
    pBackBuffer->Release( );
}

void CleanupRenderTarget( )
{
    if ( g_mainRenderTargetView ) { g_mainRenderTargetView->Release( ); g_mainRenderTargetView = NULL; }
}

extern IMGUI_IMPL_API LRESULT ImGui_ImplWin32_WndProcHandler( HWND hWnd , UINT msg , WPARAM wParam , LPARAM lParam );

LRESULT WINAPI WndProc( HWND hWnd , UINT msg , WPARAM wParam , LPARAM lParam )
{
    if ( ImGui_ImplWin32_WndProcHandler( hWnd , msg , wParam , lParam ) )
        return true;

    switch ( msg )
    {
    case WM_SIZE:
        if ( g_pd3dDevice != NULL && wParam != SIZE_MINIMIZED )
        {
            CleanupRenderTarget( );
            g_pSwapChain->ResizeBuffers( 0 , (UINT)LOWORD( lParam ) , (UINT)HIWORD( lParam ) , DXGI_FORMAT_UNKNOWN , 0 );
            CreateRenderTarget( );
        }
        return 0;
    case WM_SYSCOMMAND:
        if ( ( wParam & 0xfff0 ) == SC_KEYMENU )
            return 0;
        break;
    case WM_DESTROY:
        PostQuitMessage( 0 );
        return 0;
    }
    return ::DefWindowProc( hWnd , msg , wParam , lParam );
}