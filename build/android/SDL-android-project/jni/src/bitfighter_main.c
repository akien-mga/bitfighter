
#include "android/log.h"
#include "SDL.h"
#include "dlfcn.h"
#include "GLES/gl.h"

#define TAG "Bitfighter Loader"

typedef  (*Bitfighter_Game)(char**);

main(int argc, char *argv[]){
	void *handle;
	char *error;
	Bitfighter_Game Game;


        __android_log_print(ANDROID_LOG_INFO, TAG, "Bitfighter being loaded");
	handle = dlopen("libmain.so", RTLD_NOW|RTLD_GLOBAL);
	if(!handle){
		__android_log_print(ANDROID_LOG_INFO, TAG, dlerror());
		__android_log_print(ANDROID_LOG_INFO, TAG, "error dlopen");
		exit(EXIT_FAILURE);
	}
	dlerror();

        __android_log_print(ANDROID_LOG_INFO, TAG, "HWEngine successfully loaded..");


	Game = (Bitfighter_Game) dlsym(handle,"Game");
	if((error = dlerror()) != NULL){
		__android_log_print(ANDROID_LOG_INFO, TAG, error);
		__android_log_print(ANDROID_LOG_INFO, TAG, "error dlsym");
		exit(EXIT_FAILURE);
	}
	__android_log_print(ANDROID_LOG_INFO, TAG, "dlsym succeeded");
	Game(argv);
	__android_log_print(ANDROID_LOG_INFO, TAG, "Game() ended");

	dlclose(handle);
}
