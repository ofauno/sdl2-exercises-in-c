$ brew install sdl2_ttf --universal


$ gcc -std=c11 -Wall -Wextra -pedantic -o BIN.exe FILE.c -I/.../homebrew/include -I/.../homebrew/Cellar/sdl2_image/2.0.1_1/include -L/.../homebrew/lib -lSDL2 -lSDL2_image

$ tree /.../homebrew/include/sdl2
├── SDL.h -> ../../Cellar/sdl2/2.0.4/include/SDL2/SDL.h
├── SDL_assert.h -> ../../Cellar/sdl2/2.0.4/include/SDL2/SDL_assert.h
├── SDL_atomic.h -> ../../Cellar/sdl2/2.0.4/include/SDL2/SDL_atomic.h
├── SDL_audio.h -> ../../Cellar/sdl2/2.0.4/include/SDL2/SDL_audio.h
├── SDL_bits.h -> ../../Cellar/sdl2/2.0.4/include/SDL2/SDL_bits.h
├── SDL_blendmode.h -> ../../Cellar/sdl2/2.0.4/include/SDL2/SDL_blendmode.h
├── SDL_clipboard.h -> ../../Cellar/sdl2/2.0.4/include/SDL2/SDL_clipboard.h
├── SDL_config.h -> ../../Cellar/sdl2/2.0.4/include/SDL2/SDL_config.h
├── SDL_cpuinfo.h -> ../../Cellar/sdl2/2.0.4/include/SDL2/SDL_cpuinfo.h
├── SDL_egl.h -> ../../Cellar/sdl2/2.0.4/include/SDL2/SDL_egl.h
├── SDL_endian.h -> ../../Cellar/sdl2/2.0.4/include/SDL2/SDL_endian.h
├── SDL_error.h -> ../../Cellar/sdl2/2.0.4/include/SDL2/SDL_error.h
├── SDL_events.h -> ../../Cellar/sdl2/2.0.4/include/SDL2/SDL_events.h
├── SDL_filesystem.h -> ../../Cellar/sdl2/2.0.4/include/SDL2/SDL_filesystem.h
├── SDL_gamecontroller.h -> ../../Cellar/sdl2/2.0.4/include/SDL2/SDL_gamecontroller.h
├── SDL_gesture.h -> ../../Cellar/sdl2/2.0.4/include/SDL2/SDL_gesture.h
├── SDL_haptic.h -> ../../Cellar/sdl2/2.0.4/include/SDL2/SDL_haptic.h
├── SDL_hints.h -> ../../Cellar/sdl2/2.0.4/include/SDL2/SDL_hints.h
├── SDL_image.h -> ../../Cellar/sdl2_image/2.0.1_1/include/SDL2/SDL_image.h
├── SDL_joystick.h -> ../../Cellar/sdl2/2.0.4/include/SDL2/SDL_joystick.h
├── SDL_keyboard.h -> ../../Cellar/sdl2/2.0.4/include/SDL2/SDL_keyboard.h
├── SDL_keycode.h -> ../../Cellar/sdl2/2.0.4/include/SDL2/SDL_keycode.h
├── SDL_loadso.h -> ../../Cellar/sdl2/2.0.4/include/SDL2/SDL_loadso.h
├── SDL_log.h -> ../../Cellar/sdl2/2.0.4/include/SDL2/SDL_log.h
├── SDL_main.h -> ../../Cellar/sdl2/2.0.4/include/SDL2/SDL_main.h
├── SDL_messagebox.h -> ../../Cellar/sdl2/2.0.4/include/SDL2/SDL_messagebox.h
├── SDL_mouse.h -> ../../Cellar/sdl2/2.0.4/include/SDL2/SDL_mouse.h
├── SDL_mutex.h -> ../../Cellar/sdl2/2.0.4/include/SDL2/SDL_mutex.h
├── SDL_name.h -> ../../Cellar/sdl2/2.0.4/include/SDL2/SDL_name.h
├── SDL_opengl.h -> ../../Cellar/sdl2/2.0.4/include/SDL2/SDL_opengl.h
├── SDL_opengl_glext.h -> ../../Cellar/sdl2/2.0.4/include/SDL2/SDL_opengl_glext.h
├── SDL_opengles.h -> ../../Cellar/sdl2/2.0.4/include/SDL2/SDL_opengles.h
├── SDL_opengles2.h -> ../../Cellar/sdl2/2.0.4/include/SDL2/SDL_opengles2.h
├── SDL_opengles2_gl2.h -> ../../Cellar/sdl2/2.0.4/include/SDL2/SDL_opengles2_gl2.h
├── SDL_opengles2_gl2ext.h -> ../../Cellar/sdl2/2.0.4/include/SDL2/SDL_opengles2_gl2ext.h
├── SDL_opengles2_gl2platform.h -> ../../Cellar/sdl2/2.0.4/include/SDL2/SDL_opengles2_gl2platform.h
├── SDL_opengles2_khrplatform.h -> ../../Cellar/sdl2/2.0.4/include/SDL2/SDL_opengles2_khrplatform.h
├── SDL_pixels.h -> ../../Cellar/sdl2/2.0.4/include/SDL2/SDL_pixels.h
├── SDL_platform.h -> ../../Cellar/sdl2/2.0.4/include/SDL2/SDL_platform.h
├── SDL_power.h -> ../../Cellar/sdl2/2.0.4/include/SDL2/SDL_power.h
├── SDL_quit.h -> ../../Cellar/sdl2/2.0.4/include/SDL2/SDL_quit.h
├── SDL_rect.h -> ../../Cellar/sdl2/2.0.4/include/SDL2/SDL_rect.h
├── SDL_render.h -> ../../Cellar/sdl2/2.0.4/include/SDL2/SDL_render.h
├── SDL_revision.h -> ../../Cellar/sdl2/2.0.4/include/SDL2/SDL_revision.h
├── SDL_rwops.h -> ../../Cellar/sdl2/2.0.4/include/SDL2/SDL_rwops.h
├── SDL_scancode.h -> ../../Cellar/sdl2/2.0.4/include/SDL2/SDL_scancode.h
├── SDL_shape.h -> ../../Cellar/sdl2/2.0.4/include/SDL2/SDL_shape.h
├── SDL_stdinc.h -> ../../Cellar/sdl2/2.0.4/include/SDL2/SDL_stdinc.h
├── SDL_surface.h -> ../../Cellar/sdl2/2.0.4/include/SDL2/SDL_surface.h
├── SDL_system.h -> ../../Cellar/sdl2/2.0.4/include/SDL2/SDL_system.h
├── SDL_syswm.h -> ../../Cellar/sdl2/2.0.4/include/SDL2/SDL_syswm.h
├── SDL_test.h -> ../../Cellar/sdl2/2.0.4/include/SDL2/SDL_test.h
├── SDL_test_assert.h -> ../../Cellar/sdl2/2.0.4/include/SDL2/SDL_test_assert.h
├── SDL_test_common.h -> ../../Cellar/sdl2/2.0.4/include/SDL2/SDL_test_common.h
├── SDL_test_compare.h -> ../../Cellar/sdl2/2.0.4/include/SDL2/SDL_test_compare.h
├── SDL_test_crc32.h -> ../../Cellar/sdl2/2.0.4/include/SDL2/SDL_test_crc32.h
├── SDL_test_font.h -> ../../Cellar/sdl2/2.0.4/include/SDL2/SDL_test_font.h
├── SDL_test_fuzzer.h -> ../../Cellar/sdl2/2.0.4/include/SDL2/SDL_test_fuzzer.h
├── SDL_test_harness.h -> ../../Cellar/sdl2/2.0.4/include/SDL2/SDL_test_harness.h
├── SDL_test_images.h -> ../../Cellar/sdl2/2.0.4/include/SDL2/SDL_test_images.h
├── SDL_test_log.h -> ../../Cellar/sdl2/2.0.4/include/SDL2/SDL_test_log.h
├── SDL_test_md5.h -> ../../Cellar/sdl2/2.0.4/include/SDL2/SDL_test_md5.h
├── SDL_test_random.h -> ../../Cellar/sdl2/2.0.4/include/SDL2/SDL_test_random.h
├── SDL_thread.h -> ../../Cellar/sdl2/2.0.4/include/SDL2/SDL_thread.h
├── SDL_timer.h -> ../../Cellar/sdl2/2.0.4/include/SDL2/SDL_timer.h
├── SDL_touch.h -> ../../Cellar/sdl2/2.0.4/include/SDL2/SDL_touch.h
├── SDL_ttf.h -> ../../Cellar/sdl2_ttf/2.0.13/include/SDL2/SDL_ttf.h
├── SDL_types.h -> ../../Cellar/sdl2/2.0.4/include/SDL2/SDL_types.h
├── SDL_version.h -> ../../Cellar/sdl2/2.0.4/include/SDL2/SDL_version.h
├── SDL_video.h -> ../../Cellar/sdl2/2.0.4/include/SDL2/SDL_video.h
├── begin_code.h -> ../../Cellar/sdl2/2.0.4/include/SDL2/begin_code.h
└── close_code.h -> ../../Cellar/sdl2/2.0.4/include/SDL2/close_code.h

0 directories, 72 files

tree /.../homebrew/Cellar/sdl2_image/2.0.1_1/include
└── SDL2
    └── SDL_image.h

1 directory, 1 file

tree /.../homebrew/lib
├── cmake
├── libSDL2-2.0.0.dylib -> ../Cellar/sdl2/2.0.4/lib/libSDL2-2.0.0.dylib
├── libSDL2.a -> ../Cellar/sdl2/2.0.4/lib/libSDL2.a
├── libSDL2.dylib -> ../Cellar/sdl2/2.0.4/lib/libSDL2.dylib
├── libSDL2_image-2.0.0.dylib -> ../Cellar/sdl2_image/2.0.1_1/lib/libSDL2_image-2.0.0.dylib
├── libSDL2_image.a -> ../Cellar/sdl2_image/2.0.1_1/lib/libSDL2_image.a
├── libSDL2_image.dylib -> ../Cellar/sdl2_image/2.0.1_1/lib/libSDL2_image.dylib
├── libSDL2_test.a -> ../Cellar/sdl2/2.0.4/lib/libSDL2_test.a
├── libSDL2_ttf-2.0.0.dylib -> ../Cellar/sdl2_ttf/2.0.13/lib/libSDL2_ttf-2.0.0.dylib
├── libSDL2_ttf.a -> ../Cellar/sdl2_ttf/2.0.13/lib/libSDL2_ttf.a
├── libSDL2_ttf.dylib -> ../Cellar/sdl2_ttf/2.0.13/lib/libSDL2_ttf.dylib
├── libSDL2main.a -> ../Cellar/sdl2/2.0.4/lib/libSDL2main.a
├── libboost_atomic-mt.a -> ../Cellar/boost/1.60.0_1/lib/libboost_atomic-mt.a
├── libboost_atomic-mt.dylib -> ../Cellar/boost/1.60.0_1/lib/libboost_atomic-mt.dylib
├── libboost_chrono-mt.a -> ../Cellar/boost/1.60.0_1/lib/libboost_chrono-mt.a
├── libboost_chrono-mt.dylib -> ../Cellar/boost/1.60.0_1/lib/libboost_chrono-mt.dylib
├── libboost_chrono.a -> ../Cellar/boost/1.60.0_1/lib/libboost_chrono.a
├── libboost_chrono.dylib -> ../Cellar/boost/1.60.0_1/lib/libboost_chrono.dylib
├── libboost_container-mt.a -> ../Cellar/boost/1.60.0_1/lib/libboost_container-mt.a
├── libboost_container-mt.dylib -> ../Cellar/boost/1.60.0_1/lib/libboost_container-mt.dylib
├── libboost_container.a -> ../Cellar/boost/1.60.0_1/lib/libboost_container.a
├── libboost_container.dylib -> ../Cellar/boost/1.60.0_1/lib/libboost_container.dylib
├── libboost_context-mt.a -> ../Cellar/boost/1.60.0_1/lib/libboost_context-mt.a
├── libboost_context-mt.dylib -> ../Cellar/boost/1.60.0_1/lib/libboost_context-mt.dylib
├── libboost_coroutine-mt.a -> ../Cellar/boost/1.60.0_1/lib/libboost_coroutine-mt.a
├── libboost_coroutine-mt.dylib -> ../Cellar/boost/1.60.0_1/lib/libboost_coroutine-mt.dylib
├── libboost_coroutine.a -> ../Cellar/boost/1.60.0_1/lib/libboost_coroutine.a
├── libboost_coroutine.dylib -> ../Cellar/boost/1.60.0_1/lib/libboost_coroutine.dylib
├── libboost_date_time-mt.a -> ../Cellar/boost/1.60.0_1/lib/libboost_date_time-mt.a
├── libboost_date_time-mt.dylib -> ../Cellar/boost/1.60.0_1/lib/libboost_date_time-mt.dylib
├── libboost_date_time.a -> ../Cellar/boost/1.60.0_1/lib/libboost_date_time.a
├── libboost_date_time.dylib -> ../Cellar/boost/1.60.0_1/lib/libboost_date_time.dylib
├── libboost_exception-mt.a -> ../Cellar/boost/1.60.0_1/lib/libboost_exception-mt.a
├── libboost_exception.a -> ../Cellar/boost/1.60.0_1/lib/libboost_exception.a
├── libboost_filesystem-mt.a -> ../Cellar/boost/1.60.0_1/lib/libboost_filesystem-mt.a
├── libboost_filesystem-mt.dylib -> ../Cellar/boost/1.60.0_1/lib/libboost_filesystem-mt.dylib
├── libboost_filesystem.a -> ../Cellar/boost/1.60.0_1/lib/libboost_filesystem.a
├── libboost_filesystem.dylib -> ../Cellar/boost/1.60.0_1/lib/libboost_filesystem.dylib
├── libboost_graph-mt.a -> ../Cellar/boost/1.60.0_1/lib/libboost_graph-mt.a
├── libboost_graph-mt.dylib -> ../Cellar/boost/1.60.0_1/lib/libboost_graph-mt.dylib
├── libboost_graph.a -> ../Cellar/boost/1.60.0_1/lib/libboost_graph.a
├── libboost_graph.dylib -> ../Cellar/boost/1.60.0_1/lib/libboost_graph.dylib
├── libboost_iostreams-mt.a -> ../Cellar/boost/1.60.0_1/lib/libboost_iostreams-mt.a
├── libboost_iostreams-mt.dylib -> ../Cellar/boost/1.60.0_1/lib/libboost_iostreams-mt.dylib
├── libboost_iostreams.a -> ../Cellar/boost/1.60.0_1/lib/libboost_iostreams.a
├── libboost_iostreams.dylib -> ../Cellar/boost/1.60.0_1/lib/libboost_iostreams.dylib
├── libboost_locale-mt.a -> ../Cellar/boost/1.60.0_1/lib/libboost_locale-mt.a
├── libboost_locale-mt.dylib -> ../Cellar/boost/1.60.0_1/lib/libboost_locale-mt.dylib
├── libboost_log-mt.a -> ../Cellar/boost/1.60.0_1/lib/libboost_log-mt.a
├── libboost_log-mt.dylib -> ../Cellar/boost/1.60.0_1/lib/libboost_log-mt.dylib
├── libboost_log.a -> ../Cellar/boost/1.60.0_1/lib/libboost_log.a
├── libboost_log.dylib -> ../Cellar/boost/1.60.0_1/lib/libboost_log.dylib
├── libboost_log_setup-mt.a -> ../Cellar/boost/1.60.0_1/lib/libboost_log_setup-mt.a
├── libboost_log_setup-mt.dylib -> ../Cellar/boost/1.60.0_1/lib/libboost_log_setup-mt.dylib
├── libboost_log_setup.a -> ../Cellar/boost/1.60.0_1/lib/libboost_log_setup.a
├── libboost_log_setup.dylib -> ../Cellar/boost/1.60.0_1/lib/libboost_log_setup.dylib
├── libboost_math_c99-mt.a -> ../Cellar/boost/1.60.0_1/lib/libboost_math_c99-mt.a
├── libboost_math_c99-mt.dylib -> ../Cellar/boost/1.60.0_1/lib/libboost_math_c99-mt.dylib
├── libboost_math_c99.a -> ../Cellar/boost/1.60.0_1/lib/libboost_math_c99.a
├── libboost_math_c99.dylib -> ../Cellar/boost/1.60.0_1/lib/libboost_math_c99.dylib
├── libboost_math_c99f-mt.a -> ../Cellar/boost/1.60.0_1/lib/libboost_math_c99f-mt.a
├── libboost_math_c99f-mt.dylib -> ../Cellar/boost/1.60.0_1/lib/libboost_math_c99f-mt.dylib
├── libboost_math_c99f.a -> ../Cellar/boost/1.60.0_1/lib/libboost_math_c99f.a
├── libboost_math_c99f.dylib -> ../Cellar/boost/1.60.0_1/lib/libboost_math_c99f.dylib
├── libboost_math_c99l-mt.a -> ../Cellar/boost/1.60.0_1/lib/libboost_math_c99l-mt.a
├── libboost_math_c99l-mt.dylib -> ../Cellar/boost/1.60.0_1/lib/libboost_math_c99l-mt.dylib
├── libboost_math_c99l.a -> ../Cellar/boost/1.60.0_1/lib/libboost_math_c99l.a
├── libboost_math_c99l.dylib -> ../Cellar/boost/1.60.0_1/lib/libboost_math_c99l.dylib
├── libboost_math_tr1-mt.a -> ../Cellar/boost/1.60.0_1/lib/libboost_math_tr1-mt.a
├── libboost_math_tr1-mt.dylib -> ../Cellar/boost/1.60.0_1/lib/libboost_math_tr1-mt.dylib
├── libboost_math_tr1.a -> ../Cellar/boost/1.60.0_1/lib/libboost_math_tr1.a
├── libboost_math_tr1.dylib -> ../Cellar/boost/1.60.0_1/lib/libboost_math_tr1.dylib
├── libboost_math_tr1f-mt.a -> ../Cellar/boost/1.60.0_1/lib/libboost_math_tr1f-mt.a
├── libboost_math_tr1f-mt.dylib -> ../Cellar/boost/1.60.0_1/lib/libboost_math_tr1f-mt.dylib
├── libboost_math_tr1f.a -> ../Cellar/boost/1.60.0_1/lib/libboost_math_tr1f.a
├── libboost_math_tr1f.dylib -> ../Cellar/boost/1.60.0_1/lib/libboost_math_tr1f.dylib
├── libboost_math_tr1l-mt.a -> ../Cellar/boost/1.60.0_1/lib/libboost_math_tr1l-mt.a
├── libboost_math_tr1l-mt.dylib -> ../Cellar/boost/1.60.0_1/lib/libboost_math_tr1l-mt.dylib
├── libboost_math_tr1l.a -> ../Cellar/boost/1.60.0_1/lib/libboost_math_tr1l.a
├── libboost_math_tr1l.dylib -> ../Cellar/boost/1.60.0_1/lib/libboost_math_tr1l.dylib
├── libboost_prg_exec_monitor-mt.a -> ../Cellar/boost/1.60.0_1/lib/libboost_prg_exec_monitor-mt.a
├── libboost_prg_exec_monitor-mt.dylib -> ../Cellar/boost/1.60.0_1/lib/libboost_prg_exec_monitor-mt.dylib
├── libboost_prg_exec_monitor.a -> ../Cellar/boost/1.60.0_1/lib/libboost_prg_exec_monitor.a
├── libboost_prg_exec_monitor.dylib -> ../Cellar/boost/1.60.0_1/lib/libboost_prg_exec_monitor.dylib
├── libboost_program_options-mt.a -> ../Cellar/boost/1.60.0_1/lib/libboost_program_options-mt.a
├── libboost_program_options-mt.dylib -> ../Cellar/boost/1.60.0_1/lib/libboost_program_options-mt.dylib
├── libboost_program_options.a -> ../Cellar/boost/1.60.0_1/lib/libboost_program_options.a
├── libboost_program_options.dylib -> ../Cellar/boost/1.60.0_1/lib/libboost_program_options.dylib
├── libboost_random-mt.a -> ../Cellar/boost/1.60.0_1/lib/libboost_random-mt.a
├── libboost_random-mt.dylib -> ../Cellar/boost/1.60.0_1/lib/libboost_random-mt.dylib
├── libboost_random.a -> ../Cellar/boost/1.60.0_1/lib/libboost_random.a
├── libboost_random.dylib -> ../Cellar/boost/1.60.0_1/lib/libboost_random.dylib
├── libboost_regex-mt.a -> ../Cellar/boost/1.60.0_1/lib/libboost_regex-mt.a
├── libboost_regex-mt.dylib -> ../Cellar/boost/1.60.0_1/lib/libboost_regex-mt.dylib
├── libboost_regex.a -> ../Cellar/boost/1.60.0_1/lib/libboost_regex.a
├── libboost_regex.dylib -> ../Cellar/boost/1.60.0_1/lib/libboost_regex.dylib
├── libboost_serialization-mt.a -> ../Cellar/boost/1.60.0_1/lib/libboost_serialization-mt.a
├── libboost_serialization-mt.dylib -> ../Cellar/boost/1.60.0_1/lib/libboost_serialization-mt.dylib
├── libboost_serialization.a -> ../Cellar/boost/1.60.0_1/lib/libboost_serialization.a
├── libboost_serialization.dylib -> ../Cellar/boost/1.60.0_1/lib/libboost_serialization.dylib
├── libboost_signals-mt.a -> ../Cellar/boost/1.60.0_1/lib/libboost_signals-mt.a
├── libboost_signals-mt.dylib -> ../Cellar/boost/1.60.0_1/lib/libboost_signals-mt.dylib
├── libboost_signals.a -> ../Cellar/boost/1.60.0_1/lib/libboost_signals.a
├── libboost_signals.dylib -> ../Cellar/boost/1.60.0_1/lib/libboost_signals.dylib
├── libboost_system-mt.a -> ../Cellar/boost/1.60.0_1/lib/libboost_system-mt.a
├── libboost_system-mt.dylib -> ../Cellar/boost/1.60.0_1/lib/libboost_system-mt.dylib
├── libboost_system.a -> ../Cellar/boost/1.60.0_1/lib/libboost_system.a
├── libboost_system.dylib -> ../Cellar/boost/1.60.0_1/lib/libboost_system.dylib
├── libboost_test_exec_monitor-mt.a -> ../Cellar/boost/1.60.0_1/lib/libboost_test_exec_monitor-mt.a
├── libboost_test_exec_monitor.a -> ../Cellar/boost/1.60.0_1/lib/libboost_test_exec_monitor.a
├── libboost_thread-mt.a -> ../Cellar/boost/1.60.0_1/lib/libboost_thread-mt.a
├── libboost_thread-mt.dylib -> ../Cellar/boost/1.60.0_1/lib/libboost_thread-mt.dylib
├── libboost_timer-mt.a -> ../Cellar/boost/1.60.0_1/lib/libboost_timer-mt.a
├── libboost_timer-mt.dylib -> ../Cellar/boost/1.60.0_1/lib/libboost_timer-mt.dylib
├── libboost_timer.a -> ../Cellar/boost/1.60.0_1/lib/libboost_timer.a
├── libboost_timer.dylib -> ../Cellar/boost/1.60.0_1/lib/libboost_timer.dylib
├── libboost_type_erasure-mt.a -> ../Cellar/boost/1.60.0_1/lib/libboost_type_erasure-mt.a
├── libboost_type_erasure-mt.dylib -> ../Cellar/boost/1.60.0_1/lib/libboost_type_erasure-mt.dylib
├── libboost_type_erasure.a -> ../Cellar/boost/1.60.0_1/lib/libboost_type_erasure.a
├── libboost_type_erasure.dylib -> ../Cellar/boost/1.60.0_1/lib/libboost_type_erasure.dylib
├── libboost_unit_test_framework-mt.a -> ../Cellar/boost/1.60.0_1/lib/libboost_unit_test_framework-mt.a
├── libboost_unit_test_framework-mt.dylib -> ../Cellar/boost/1.60.0_1/lib/libboost_unit_test_framework-mt.dylib
├── libboost_unit_test_framework.a -> ../Cellar/boost/1.60.0_1/lib/libboost_unit_test_framework.a
├── libboost_unit_test_framework.dylib -> ../Cellar/boost/1.60.0_1/lib/libboost_unit_test_framework.dylib
├── libboost_wave-mt.a -> ../Cellar/boost/1.60.0_1/lib/libboost_wave-mt.a
├── libboost_wave-mt.dylib -> ../Cellar/boost/1.60.0_1/lib/libboost_wave-mt.dylib
├── libboost_wserialization-mt.a -> ../Cellar/boost/1.60.0_1/lib/libboost_wserialization-mt.a
├── libboost_wserialization-mt.dylib -> ../Cellar/boost/1.60.0_1/lib/libboost_wserialization-mt.dylib
├── libboost_wserialization.a -> ../Cellar/boost/1.60.0_1/lib/libboost_wserialization.a
├── libboost_wserialization.dylib -> ../Cellar/boost/1.60.0_1/lib/libboost_wserialization.dylib
├── libcapnp-rpc.a -> ../Cellar/capnp/0.5.3/lib/libcapnp-rpc.a
├── libcapnp.a -> ../Cellar/capnp/0.5.3/lib/libcapnp.a
├── libcapnpc.a -> ../Cellar/capnp/0.5.3/lib/libcapnpc.a
├── libfreetype.6.dylib -> ../Cellar/freetype/2.6.3/lib/libfreetype.6.dylib
├── libfreetype.a -> ../Cellar/freetype/2.6.3/lib/libfreetype.a
├── libfreetype.dylib -> ../Cellar/freetype/2.6.3/lib/libfreetype.dylib
├── libjpeg.8.dylib -> ../Cellar/jpeg/8d/lib/libjpeg.8.dylib
├── libjpeg.a -> ../Cellar/jpeg/8d/lib/libjpeg.a
├── libjpeg.dylib -> ../Cellar/jpeg/8d/lib/libjpeg.dylib
├── libkj-async.a -> ../Cellar/capnp/0.5.3/lib/libkj-async.a
├── libkj.a -> ../Cellar/capnp/0.5.3/lib/libkj.a
├── liblzma.5.dylib -> ../Cellar/xz/5.2.2/lib/liblzma.5.dylib
├── liblzma.a -> ../Cellar/xz/5.2.2/lib/liblzma.a
├── liblzma.dylib -> ../Cellar/xz/5.2.2/lib/liblzma.dylib
├── libmad.0.2.1.dylib -> ../Cellar/mad/0.15.1b/lib/libmad.0.2.1.dylib
├── libmad.0.dylib -> ../Cellar/mad/0.15.1b/lib/libmad.0.dylib
├── libmad.a -> ../Cellar/mad/0.15.1b/lib/libmad.a
├── libmad.dylib -> ../Cellar/mad/0.15.1b/lib/libmad.dylib
├── libpng.a -> ../Cellar/libpng/1.6.21/lib/libpng.a
├── libpng.dylib -> ../Cellar/libpng/1.6.21/lib/libpng.dylib
├── libpng16.16.dylib -> ../Cellar/libpng/1.6.21/lib/libpng16.16.dylib
├── libpng16.a -> ../Cellar/libpng/1.6.21/lib/libpng16.a
├── libpng16.dylib -> ../Cellar/libpng/1.6.21/lib/libpng16.dylib
├── libsox.3.dylib -> ../Cellar/sox/14.4.2/lib/libsox.3.dylib
├── libsox.a -> ../Cellar/sox/14.4.2/lib/libsox.a
├── libsox.dylib -> ../Cellar/sox/14.4.2/lib/libsox.dylib
├── libtiff.5.dylib -> ../Cellar/libtiff/4.0.6/lib/libtiff.5.dylib
├── libtiff.a -> ../Cellar/libtiff/4.0.6/lib/libtiff.a
├── libtiff.dylib -> ../Cellar/libtiff/4.0.6/lib/libtiff.dylib
├── libtiffxx.5.dylib -> ../Cellar/libtiff/4.0.6/lib/libtiffxx.5.dylib
├── libtiffxx.a -> ../Cellar/libtiff/4.0.6/lib/libtiffxx.a
├── libtiffxx.dylib -> ../Cellar/libtiff/4.0.6/lib/libtiffxx.dylib
├── libwebp.6.dylib -> ../Cellar/webp/0.5.0/lib/libwebp.6.dylib
├── libwebp.a -> ../Cellar/webp/0.5.0/lib/libwebp.a
├── libwebp.dylib -> ../Cellar/webp/0.5.0/lib/libwebp.dylib
├── libwebpdecoder.2.dylib -> ../Cellar/webp/0.5.0/lib/libwebpdecoder.2.dylib
├── libwebpdecoder.a -> ../Cellar/webp/0.5.0/lib/libwebpdecoder.a
├── libwebpdecoder.dylib -> ../Cellar/webp/0.5.0/lib/libwebpdecoder.dylib
├── libwebpdemux.2.dylib -> ../Cellar/webp/0.5.0/lib/libwebpdemux.2.dylib
├── libwebpdemux.a -> ../Cellar/webp/0.5.0/lib/libwebpdemux.a
├── libwebpdemux.dylib -> ../Cellar/webp/0.5.0/lib/libwebpdemux.dylib
├── libwebpmux.2.dylib -> ../Cellar/webp/0.5.0/lib/libwebpmux.2.dylib
├── libwebpmux.a -> ../Cellar/webp/0.5.0/lib/libwebpmux.a
├── libwebpmux.dylib -> ../Cellar/webp/0.5.0/lib/libwebpmux.dylib
├── pkgconfig
└── python2.7

3 directories, 173 files
