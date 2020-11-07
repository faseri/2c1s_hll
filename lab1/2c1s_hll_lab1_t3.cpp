#include <stdlib.h>
#include <cstdlib>
#include <iostream>

#include "SDL2/SDL.h"

char langn=0;
void fillScreen(SDL_Window *window) {
	SDL_Surface *screen = SDL_GetWindowSurface(window);

	SDL_FillRect(screen, NULL, SDL_MapRGB(screen->format, rand() % 255, rand() % 255, rand() % 255));

	SDL_UpdateWindowSurface(window);
}

int asmFunction(void) {
	static int internalValue = 1;

#ifdef __GNUC__
	__asm__("movl %0, %%eax\n\t"
		"add %%eax, %0"
		: "=r" (internalValue)
		: "r" (internalValue));
#elif _MSC_VER
	_asm {
		mov eax, internalValue
			add internalValue, eax
	};
#endif

	return internalValue;
}

int eventFilter(void *userdata, SDL_Event *event) {
	switch (event->type) {
	case SDL_KEYDOWN:
		if (event->key.keysym.sym == SDLK_q && event->key.keysym.mod == KMOD_LCTRL) {
			SDL_Event exitEvent = { SDL_QUIT };
			SDL_PushEvent(&exitEvent);
		}
		switch(langn){
			case 1: SDL_Log("Нажата клавиша %d", event->key.keysym.sym); break;
			case 2: SDL_Log("Нажата клавиша %d", event->key.keysym.sym);
			case 0:	SDL_Log("key Down %d", event->key.keysym.sym);
		}
		break;
	case SDL_KEYUP:
		switch(langn){
						case 1: SDL_Log("Поднята клавиша %d", event->key.keysym.sym); break;
						case 2: SDL_Log("Поднята клавиша %d", event->key.keysym.sym);
						case 0:	SDL_Log("key Up %d", event->key.keysym.sym);

					}
		break;
	case SDL_TEXTEDITING:
		switch(langn){
						case 1: SDL_Log("Редактирование текста с клавиатуры (составное). Составлено слово '%s', начало курсора на %d и длина выбранной части %d", event->edit.text, event->edit.start, event->edit.length); break;
						case 2: SDL_Log("Редактирование текста с клавиатуры (составное). Составлено слово '%s', начало курсора на %d и длина выбранной части %d", event->edit.text, event->edit.start, event->edit.length);
						case 0:	SDL_Log("Keyboard text editing (composition). Composition is '%s', cursor start from %d and selection lenght is %d", event->edit.text, event->edit.start, event->edit.length);
					}

		break;
	case SDL_TEXTINPUT:
		switch(langn){
						case 1: SDL_Log("Ввод с клавиатуры. Текст: '%s'", event->text.text); break;
						case 2: SDL_Log("Ввод с клавиатуры. Текст: '%s'", event->text.text);
						case 0:	SDL_Log("Keyboard text input. Text is '%s'", event->text.text);

					}

		break;
	case SDL_FINGERMOTION:
		switch(langn){
						case 1: SDL_Log("Палец: %i, x: %i, y: %i", event->tfinger.fingerId, event->tfinger.x, event->tfinger.y); break;
						case 2: SDL_Log("Палец: %i, x: %i, y: %i", event->tfinger.fingerId, event->tfinger.x, event->tfinger.y);
						case 0:	SDL_Log("Finger: %i, x: %i, y: %i", event->tfinger.fingerId, event->tfinger.x, event->tfinger.y);

					}

		break;
	case SDL_FINGERDOWN:
		switch(langn){
						case 1: SDL_Log("Палец: %lld нажал - x: %i, y: %i",
								event->tfinger.fingerId, event->tfinger.x, event->tfinger.y); break;
						case 2:SDL_Log("Палец: %lld нажал - x: %i, y: %i",
								event->tfinger.fingerId, event->tfinger.x, event->tfinger.y);
						case 0:	SDL_Log("Finger: %lld down - x: %i, y: %i",
								event->tfinger.fingerId, event->tfinger.x, event->tfinger.y);
					}

		break;
	case SDL_FINGERUP:
		switch(langn){
						case 1: SDL_Log("Палец: %lld поднят - x: %i, y: %i", event->tfinger.fingerId, event->tfinger.x, event->tfinger.y); break;
						case 2: SDL_Log("Палец: %lld поднят - x: %i, y: %i", event->tfinger.fingerId, event->tfinger.x, event->tfinger.y);
						case 0:	SDL_Log("Finger: %lld up - x: %i, y: %i", event->tfinger.fingerId, event->tfinger.x, event->tfinger.y);

					}

		break;
	case SDL_MULTIGESTURE:
		switch(langn){
						case 1: SDL_Log("Мульти жест: x = %f, y = %f, dAng = %f, dR = %f", event->mgesture.x, event->mgesture.y, event->mgesture.dTheta, event->mgesture.dDist);
						SDL_Log("Мульти жест: кол-во пальцев = %i", event->mgesture.numFingers); break;
						case 2: SDL_Log("Мульти жест: x = %f, y = %f, dAng = %f, dR = %f", event->mgesture.x, event->mgesture.y, event->mgesture.dTheta, event->mgesture.dDist);
						SDL_Log("Мульти жест: кол-во пальцев = %i", event->mgesture.numFingers);
						case 0:	SDL_Log("Multi gesture: x = %f, y = %f, dAng = %f, dR = %f", event->mgesture.x, event->mgesture.y, event->mgesture.dTheta, event->mgesture.dDist);
						SDL_Log("Multi gesture: numDownTouch = %i", event->mgesture.numFingers);

					}

		break;
	case SDL_DOLLARGESTURE:
		switch(langn){
						case 1: SDL_Log("Жест %lld выполнен, ошибка: %f", event->dgesture.gestureId, event->dgesture.error); break;
						case 2: SDL_Log("Жест %lld выполнен, ошибка: %f", event->dgesture.gestureId, event->dgesture.error);
						case 0:	SDL_Log("Gesture %lld performed, error: %f", event->dgesture.gestureId, event->dgesture.error);

					}

		break;
	case SDL_DOLLARRECORD:
		switch(langn){
						case 1: SDL_Log("Записан жест: %lld", event->dgesture.gestureId); break;
						case 2: SDL_Log("Записан жест: %lld", event->dgesture.gestureId);
						case 0:	SDL_Log("Recorded gesture: %lld", event->dgesture.gestureId);
					}
		break;
	case SDL_MOUSEMOTION:
		switch(langn){
						case 1: SDL_Log("Мышь сдвинута. X=%d, Y=%d, относ Х=%d, относ У=%d", event->motion.x, event->motion.y, event->motion.xrel, event->motion.yrel); break;
						case 2: SDL_Log("Мышь сдвинута. X=%d, Y=%d, относ Х=%d, относ У=%d", event->motion.x, event->motion.y, event->motion.xrel, event->motion.yrel);
						case 0:	SDL_Log("Mouse Move. X=%d, Y=%d, RelativeX=%d, RelativeY=%d", event->motion.x, event->motion.y, event->motion.xrel, event->motion.yrel);

					}

		break;
	case SDL_MOUSEBUTTONDOWN:
		if (event->button.button == SDL_BUTTON_LEFT)
			asmFunction();
		switch(langn){
						case 1: SDL_Log("Нажатие кнопки мыши %u", event->button.button); break;
						case 2: SDL_Log("Нажатие кнопки мыши %u", event->button.button);
						case 0:	SDL_Log("Mouse Button Down %u", event->button.button);
					}
		break;
	case SDL_MOUSEBUTTONUP:
		switch(langn){
						case 1: SDL_Log("Кнопку мыши отпустили %u", event->button.button); break;
						case 2: SDL_Log("Кнопку мыши отпустили %u", event->button.button);
						case 0:	SDL_Log("Mouse Button Up %u", event->button.button);
					}
		break;
	case SDL_MOUSEWHEEL:
		switch(langn){
						case 1: SDL_Log("Колесо мыши X=%d, Y=%d", event->wheel.x, event->wheel.y); break;
						case 2: SDL_Log("Колесо мыши X=%d, Y=%d", event->wheel.x, event->wheel.y);
						case 0:	SDL_Log("Mouse Wheel X=%d, Y=%d", event->wheel.x, event->wheel.y);

					}

		break;
	case SDL_QUIT:
		switch(langn){
						case 1: SDL_Log("Пользователь решил выйти из программы"); break;
						case 2: SDL_Log("Пользователь решил выйти из программы");
						case 0:	SDL_Log("User-requested quit");

					}

		return 1;
	case SDL_WINDOWEVENT:
		switch (event->window.event) {
		case SDL_WINDOWEVENT_SHOWN:
			switch(langn){
							case 1: SDL_Log("Окно %d показано", event->window.windowID);  break;
							case 2: SDL_Log("Окно %d показано", event->window.windowID);
							case 0:	SDL_Log("Window %d shown", event->window.windowID);
						}
			break;
		case SDL_WINDOWEVENT_HIDDEN:
			switch(langn){
							case 1: SDL_Log("Окно %d скрыто", event->window.windowID); break;
							case 2: SDL_Log("Окно %d скрыто", event->window.windowID);
							case 0:	SDL_Log("Mouse left window %d", event->window.windowID);

						}

			break;
		case SDL_WINDOWEVENT_EXPOSED:
			switch(langn){
							case 1: SDL_Log("Окно %d развернуто", event->window.windowID); break;
							case 2: SDL_Log("Окно %d развернуто", event->window.windowID);
							case 0:	SDL_Log("Window %d exposed", event->window.windowID);

						}
			fillScreen(SDL_GetWindowFromID(event->window.windowID));
			break;
		case SDL_WINDOWEVENT_MOVED:
			switch(langn){
							case 1: SDL_Log("Окно %d сдвинуто в %d,%d", event->window.windowID, event->window.data1, event->window.data2); break;
							case 2: SDL_Log("Окно %d сдвинуто в %d,%d", event->window.windowID, event->window.data1, event->window.data2);
							case 0:	SDL_Log("Window %d moved to %d,%d", event->window.windowID, event->window.data1, event->window.data2);

						}

			break;
		case SDL_WINDOWEVENT_RESIZED:
			switch(langn){
							case 1: SDL_Log("Окно %d изменило размер %dx%d", event->window.windowID, event->window.data1, event->window.data2); break;
							case 2: SDL_Log("Окно %d изменило размер %dx%d", event->window.windowID, event->window.data1, event->window.data2);
							case 0:	SDL_Log("Window %d resized to %dx%d", event->window.windowID, event->window.data1, event->window.data2);

						}

			break;
		case SDL_WINDOWEVENT_SIZE_CHANGED:
			switch(langn){
				case 1: SDL_Log("Размер окна %d изменился %dx%d", event->window.windowID, event->window.data1, event->window.data2); break;
				case 2: SDL_Log("Размер окна %d изменился %dx%d", event->window.windowID, event->window.data1, event->window.data2);
				case 0:	SDL_Log("Window %d size changed to %dx%d", event->window.windowID, event->window.data1, event->window.data2);
			}

			break;
		case SDL_WINDOWEVENT_MINIMIZED:
			switch(langn){
				case 1: SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_INFORMATION, "Что ты делаешь?!", "Разверни меня обратно, сейчас-же!", NULL); break;
				case 2: SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_INFORMATION, "Что ты делаешь?! What are you doing!?", "Разверни меня обратно, сейчас-же! MAXIMIZE ME! NOW!", NULL); break;
				case 0:	SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_INFORMATION, "Something going wrong", "Find me! I'm scared", NULL);
			}
			switch(langn){
				case 1: SDL_Log("Окно %d свернуто", event->window.windowID); break;
				case 2: SDL_Log("Окно %d свернуто", event->window.windowID);
				case 0:	SDL_Log("Window %d minimized", event->window.windowID);
			}

			break;
		case SDL_WINDOWEVENT_MAXIMIZED:
			switch(langn){
				case 1: SDL_Log("Окно %d развернуто", event->window.windowID); break;
				case 2: SDL_Log("Окно %d развернуто", event->window.windowID);
				case 0:	SDL_Log("Window %d maximized", event->window.windowID);
			}

			break;
		case SDL_WINDOWEVENT_RESTORED:
			switch(langn){
							case 1: SDL_Log("Окно %d восстановлено", event->window.windowID); break;
							case 2: SDL_Log("Окно %d восстановлено", event->window.windowID);
							case 0:	SDL_Log("Window %d restored", event->window.windowID);

						}

			break;
		case SDL_WINDOWEVENT_ENTER:
			switch(langn){
				case 1: SDL_Log("Мышь вошла в окно %d", event->window.windowID); break;
				case 2: SDL_Log("Мышь вошла в окно %d", event->window.windowID);
				case 0:	SDL_Log("Mouse entered window %d", event->window.windowID);
			}
			break;
		case SDL_WINDOWEVENT_LEAVE:
			switch(langn){
				case 1: SDL_Log("Мышь покинула окно %d", event->window.windowID); break;
				case 2: SDL_Log("Мышь покинула окно %d", event->window.windowID);
				case 0:	SDL_Log("Mouse left window %d", event->window.windowID);

			}
			break;
		case SDL_WINDOWEVENT_FOCUS_GAINED:
			switch(langn){
				case 1: SDL_Log("Окно %d получило фокус клавиатуры", event->window.windowID); break;
				case 2: SDL_Log("Окно %d получило фокус клавиатуры", event->window.windowID);
				case 0:	SDL_Log("Window %d gained keyboard focus", event->window.windowID);
			}
			break;
		case SDL_WINDOWEVENT_FOCUS_LOST:
			switch(langn){
				case 1: SDL_Log("Окно %d потеряло фокус клавиатуры", event->window.windowID); break;
				case 2: SDL_Log("Окно %d потеряло фокус клавиатуры", event->window.windowID);
				case 0:	SDL_Log("Window %d lost keyboard focus", event->window.windowID);
			}

			break;
		case SDL_WINDOWEVENT_CLOSE:
			switch(langn){
				case 1: SDL_Log("Окно %d закрыто", event->window.windowID); break;
				case 2: SDL_Log("Окно %d закрыто", event->window.windowID);
				case 0:	SDL_Log("Window %d closed", event->window.windowID);
			}

			break;
		default:
			switch(langn){
				case 1: SDL_Log("Окно %d получило неизвестный ивент %d", event->window.windowID, event->window.event); break;
				case 2: SDL_Log("Окно %d получило неизвестный ивент %d", event->window.windowID, event->window.event);
				case 0:	SDL_Log("Window %d got unknown event %d", event->window.windowID, event->window.event);
			}

			break;
		}
		break;
	default:
		switch(langn){
				case 1: SDL_Log("Получен неизвестный ивент %d", event->type); break;
				case 2: SDL_Log("Получен неизвестный ивент %d", event->type);
				case 0:	SDL_Log("Got unknown event %d", event->type);
			}
		break;
	}

	return 0;
}

Uint32 customEventFunction(Uint32 interval, void *param) {
	SDL_Event event = { SDL_WINDOWEVENT };
	switch(langn){
		case 1: SDL_Log("Сработал таймер с интервалом %d мс", interval); break;
		case 2: SDL_Log("Сработал таймер с интервалом %d мс", interval);
		case 0:	SDL_Log("Timer signaled with interval %d ms", interval);
	}
	event.window.windowID = SDL_GetWindowID((SDL_Window*)param);
	event.window.event = SDL_WINDOWEVENT_EXPOSED;

	SDL_PushEvent(&event);
	return(interval);
}
Uint32 repeatOnceFunction(Uint32 interval, void *param) {
	SDL_Event exitEvent = { SDL_QUIT };

	switch(langn){
		case 1: SDL_Log("Сработал таймер с интервалом %d мс", interval); break;
		case 2: SDL_Log("Сработал таймер с интервалом %d мс", interval);
		case 0:	SDL_Log("Timer signaled with interval %d ms", interval);
	}
	if (asmFunction() != 0) {
		SDL_HideWindow((SDL_Window*)param);
		switch(langn){
			case 1: SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_INFORMATION, "Что-то идет не так ", "Найди меня! Мне страшно", NULL); break;
			case 2: SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_INFORMATION, " Что-то идет не так Something going wrong", " Найди меня! Мне страшно Find me! I'm scared", NULL); break;
			case 0:	SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_INFORMATION, "Something going wrong", "Find me! I'm scared", NULL);
		}


		SDL_Delay(15000); /* 15 sec */
		switch(langn){
			case 1: SDL_LogWarn(SDL_LOG_CATEGORY_APPLICATION, "Ты не нашел меня! Ты меня разочаровал... Я ухожу."); break;
			case 2: SDL_LogWarn(SDL_LOG_CATEGORY_APPLICATION, "Ты не нашел меня! Ты меня разочаровал... Я ухожу."); break;
			case 0:	SDL_LogWarn(SDL_LOG_CATEGORY_APPLICATION, "You didn't find me! You disappointed me... I'm leaving.");
		}
		SDL_PushEvent(&exitEvent);
	}

	return 0;
}

void clearFunction(void) {
	SDL_Quit();
}

int main(int argc, char *argv[]) {
	SDL_Window *windowContext = NULL;
	SDL_TimerID repeatOnceFunctionTimer;
	SDL_TimerID customEventFunctionTimer;
	std::string language;

	if(argc>1){
		language = argv[1];
		if(!language.compare("russian")){
			langn=1;
		} else if(!language.compare("bilingual")){
			langn=2;
		}
	}


	atexit(clearFunction);
	srand((unsigned int)NULL);

	if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_TIMER) < 0) {
		switch(langn){
				case 1: SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "Ошибка", "Невозможно инициализировать SDL2. Больше информации в логе.", NULL);
						SDL_LogCritical(SDL_LOG_CATEGORY_APPLICATION, "Невозможно инициализировать SDL2, ошибка: %s", SDL_GetError()); break;
				case 2: SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "Ошибка", "Невозможно инициализировать SDL2. Больше информации в логе.", NULL);
						SDL_LogCritical(SDL_LOG_CATEGORY_APPLICATION, "Невозможно инициализировать SDL2, ошибка: %s", SDL_GetError());
				case 0: SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "Error", "Unable to init SDL2. See the log for more info.", NULL);
						SDL_LogCritical(SDL_LOG_CATEGORY_APPLICATION, "Unable to init SDL2, error: %s", SDL_GetError());
			}

		return 1;
	}

	SDL_SetEventFilter(eventFilter, NULL);
	switch(langn){
		case 1: SDL_Log("Создание окна "); break;
		case 2: SDL_Log("Создание окна ");
		case 0: SDL_Log("Start creating window");
	}
	if (!(windowContext = SDL_CreateWindow("SDL2: Magic Events", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 640, 480, SDL_WINDOW_ALLOW_HIGHDPI | SDL_WINDOW_RESIZABLE))) {
		switch(langn){
			case 1: SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "Ошибка", "Невозможно Создать окно. Больше информации в логе.", NULL);
					SDL_LogCritical(SDL_LOG_CATEGORY_APPLICATION, "Невозможно Создать окно, ошибка: %s", SDL_GetError()); break;
			case 2: SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "Ошибка", "Невозможно Создать окно. Больше информации в логе.", NULL);
					SDL_LogCritical(SDL_LOG_CATEGORY_APPLICATION, "Невозможно Создать окно, ошибка: %s", SDL_GetError());
			case 0: SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "Error", "Unable to create window. See the log for more info.", NULL);
					SDL_LogCritical(SDL_LOG_CATEGORY_APPLICATION, "Unable to create window, error: %s", SDL_GetError());
		}

		return 1;
	}
	else {
		switch(langn){
			case 1: SDL_Log("Успешное создание окна "); break;
			case 2: SDL_Log("Успешное создание окна ");
			case 0: SDL_Log("Creating window - succeeded");
		}

	}

	if (!(customEventFunctionTimer = SDL_AddTimer(2000 /* 2 sec */, customEventFunction, windowContext))) {

		SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "Error", "Unable to create custom event timer. See the log for more info.", windowContext);
		SDL_LogCritical(SDL_LOG_CATEGORY_APPLICATION, "Unable to create custom event timer, error: %s", SDL_GetError());
	}

	if (!(repeatOnceFunctionTimer = SDL_AddTimer(10000 /* 10 sec */, repeatOnceFunction, windowContext))) {
		switch(langn){
		case 1: SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "Ошибка", "Невозможно повторить таймер. Больше информации в логе.", windowContext);
			SDL_LogCritical(SDL_LOG_CATEGORY_APPLICATION, "Невозможно создать таймер, ошибка: %s", SDL_GetError()); break;
		case 2: SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "Ошибка", "Невозможно повторить таймер. Больше информации в логе.", windowContext);
			SDL_LogCritical(SDL_LOG_CATEGORY_APPLICATION, "Невозможно создать таймер, ошибка: %s", SDL_GetError());
		case 0: SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "Error", "Unable to create repeat once timer. See the log for more info.", windowContext);
			SDL_LogCritical(SDL_LOG_CATEGORY_APPLICATION, "Unable to create repeat once timer, error: %s", SDL_GetError());
		}
		
	}



	SDL_WaitEvent(NULL);

	SDL_RemoveTimer(repeatOnceFunctionTimer);
	SDL_RemoveTimer(customEventFunctionTimer);
	switch(langn){
	case 1: SDL_Log("Начало уничтожения окна "); break;
	case 2: SDL_Log("Начало уничтожения окна ");
	case 0: SDL_Log("Start destroing window");
	}

	SDL_DestroyWindow(windowContext);
	windowContext = NULL;
	switch(langn){
	case 1: SDL_Log("Успешное уничтожение окна "); break;
	case 2: SDL_Log("Успешное уничтожение окна ");
	case 0: SDL_Log("destroing window - succeeded");
	}


	return 0;
}
