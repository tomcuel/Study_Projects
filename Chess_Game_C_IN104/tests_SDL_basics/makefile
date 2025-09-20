build:
	gcc -Wall image.c `sdl2-config --libs --cflags` -lm -o image
	gcc -Wall audio.c `sdl2-config --libs --cflags` -lm -o audio
	gcc -Wall mouse+key.c `sdl2-config --libs --cflags` -lm -o mouse+key
	gcc double_window.c -o double_window -Iinclude -lSDL2main -lSDL2
	gcc mouse+key.c -o mouse+key.x -Iinclude -lSDL2main -lSDL2
	gcc timer.c -o timer.x -Iinclude -lSDL2main -lSDL2
	gcc mouse+key_with_countdown.c -o mouse+key_with_countdown.x -Iinclude -lSDL2main -lSDL2
	gcc double_timer.c -o double_timer.x -Iinclude -lSDL2main -lSDL2
	gcc test_click_mouse.c -o test_click_mouse.x -Iinclude -lSDL2main -lSDL2
	gcc draw_rect_borders.c -o draw_rect_borders.x -Iinclude -lSDL2main -lSDL2
	gcc test_draw_numbers.c -o test_draw_numbers.x -Iinclude -lSDL2main -lSDL2
	gcc test_audio_in_game.c -o test_audio_in_game.x -Iinclude -lSDL2main -lSDL2
	gcc test_print_letters_and_numbers.c -o test_print_letters_and_numbers.x -Iinclude -lSDL2main -lSDL2
	gcc test_blur.c -o test_blur.x -Iinclude -lSDL2main -lSDL2


realclean:
	rm -f image audio mouse+key double_window mouse+key.x timer.x mouse+key_with_countdown.x double_timer.x test_click_mouse.x draw_rect_borders.x test_draw_numbers.x test_audio_in_game.x test_print_letters_and_numbers.x test_blur.x