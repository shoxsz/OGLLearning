#ifndef _DEFINITIONS_HPP_
#define _DEFINITIONS_HPP_

#include <memory>

class SDLWindow;
class SDLMessageBox;
class ApplicationListener;

typedef std::shared_ptr<SDLWindow> SDLWindowPtr;
typedef std::shared_ptr<SDLMessageBox> SDLMessageBoxPtr;
typedef std::shared_ptr<ApplicationListener> ApplicationListenerPtr;

#endif