#include <string>
#include "GLFW/glfw3.h"
#include "Error.h"

void framebuffer_size_callback(int height,int width);
namespace InitOpengl
{
    struct windowData
    {
        int height;
        int width;
        std::string windowName;
    };

    class Window
    {
        private:
            InitOpengl::windowData windowDataHandle;

        public:
            // constructor
            Window(int height_,int width,std::string windowName)
            {
             // assigning data's to variables
             windowDataHandle.height = 100;
             windowDataHandle.width = width;
             // @usage: the window's name variable
             windowDataHandle.windowName = windowName;

             // init the opengl.
             glfwInit();};

            void addHint(int hint,int value);

            // init the opengl window;
           ErrorOpengl::Error init();

            // WARNING: the method Init already Add's the current Context Window,
            // if you want to pass other context Window
            // Use addContext Method.
            void addContext(GLFWwindow* windowHandle);

            // method for checking if opengl window is closed or not.
            bool isClosed();

            // method for updating the swap buffer and pollevents
            void update();
            // deconstructor
            ~Window();

            //variables;
            // @use: public windowHandle object, for using it in other methods and functions
            GLFWwindow* windowHandle;

    };
}
