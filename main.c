// main.c

#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <stdint.h>
#include <SDL.h>

#include "vector.h"


// Globals
SDL_Window* window;
SDL_Renderer* renderer;
SDL_Texture* texture;
uint32_t* pixels;
int pixels_w, pixels_h;
SDL_Rect window_rect;
bool is_running;
int animation_mode;

// Global state for rendering
uint32_t frame_index;

// Globals for cube
#define CUBE_POINT_COUNT (9*9*9)
vec3_t cube_model[CUBE_POINT_COUNT];
vec2_t projected_points[CUBE_POINT_COUNT];

// Camera
vec3_t camera_position = { 0.0f, 0.0f, -5.0f };

// Functions

void build_cube_model() {
	int i = 0;
	for (float x = -1; x <= 1; x += 0.25f) {
		for (float y = -1; y <= 1; y += 0.25f) {
			for (float z = -1; z <= 1; z += 0.25f) {
				vec3_t pt = { .x = x, .y = y, .z = z };
				cube_model [i++] = pt;
			}
		}
	}
}

void translate_cube_model(vec3_t offset) {
	for (int i = 0; i < CUBE_POINT_COUNT; i++) {
		vec3_t pt = cube_model[i];
		pt.x += offset.x;
		pt.y += offset.y;
		pt.z += offset.z;
		cube_model[i] = pt;
	}
}

vec2_t orthographic_project_point(vec3_t pt3d) {
	vec2_t pt2d = { .x = pt3d.x, .y = pt3d.y };
	return pt2d;
}

vec2_t perspective_project_point(vec3_t pt3d) {
	// Apply camera position
	pt3d.x -= camera_position.x;
	pt3d.y -= camera_position.y;
	pt3d.z -= camera_position.z;
	vec2_t pt2d = { .x = pt3d.x / pt3d.z, .y = pt3d.y / pt3d.z };
	return pt2d;
}

void project_model() {
	// Project the 3d model into 2d space
	for (int i = 0; i < CUBE_POINT_COUNT; i++) {
		vec3_t pt3d = cube_model[i];
		//vec2_t pt2d = orthographic_project_point(pt3d);
		vec2_t pt2d = perspective_project_point(pt3d);
		projected_points[i] = pt2d;
	}
}

void scale_projection() {
	// Apply a scaling factor to the projected points
	const int factor = 640;
	for (int i = 0; i < CUBE_POINT_COUNT; i++) {
		projected_points[i].x *= factor;
		projected_points[i].y *= factor;
	}
}

void clear(uint32_t color) {
	for (int i = 0; i < pixels_w * pixels_h; i++) {
		pixels[i] = color;
	}
}

void set_pixel(int x, int y, uint32_t color) {
	if (x < 0 || x >= pixels_w) return;
	if (y < 0 || y >= pixels_h) return;
	pixels[x + y * pixels_w] = color;
}

void draw_centered_rect(int x, int y, int w, int h, uint32_t color) {
	int top = y - h / 2;
	int left = x - w / 2;
	for (int y1 = 0; y1 < h; y1++) {
		for (int x1 = 0; x1 < w; x1++) {
			set_pixel(left + x1, top + y1, color);
		}
	}
}

bool initialize_windowing_system() {
	// Set up SDL
	if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
		fprintf(stderr, "SDL_Init() failed!\n");
		return false;
	}

	// Full screen
	SDL_DisplayMode display_mode;
	SDL_GetCurrentDisplayMode(0, &display_mode);
	window_rect.x = 0;
	window_rect.y = 0;
	window_rect.w = display_mode.w;
	window_rect.h = display_mode.h;

	// Window
	window = SDL_CreateWindow(NULL, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
		window_rect.w, window_rect.h, SDL_WINDOW_BORDERLESS);
	// options: SDL_WINDOWPOS_CENTERED, SDL_WINDOW_BORDERLESS
	if (!window) {
		fprintf(stderr, "SDL_CreateWindow() failed!\n");
		return false;
	}

	// Renderer
	renderer = SDL_CreateRenderer(window, -1, 0);
	if (!renderer) {
		fprintf(stderr, "SDL_CreateRenderer() failed!\n");
		return false;
	}

	// Texture
	pixels_w = window_rect.w;
	pixels_h = window_rect.h;
	texture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_RGBA8888,
		SDL_TEXTUREACCESS_STREAMING, pixels_w, pixels_h);
	if (!texture) {
		fprintf(stderr, "SDL_CreateTexture() failed!\n");
		return false;
	}

	// Allocate frame buffer
	pixels = (uint32_t*)malloc(pixels_w * pixels_h * sizeof(uint32_t));
	if (!pixels) {
		fprintf(stderr, "malloc() failed!\n");
		return false;
	}
	clear(0x000000FF);

	// Set up the renderer
	SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, 0); // Use no interpolation
	// Clear the window
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
	SDL_RenderClear(renderer);
	SDL_RenderPresent(renderer);

	// Reset the frame index
	frame_index = 0;

	return true;
}

void clean_up_windowing_system() {
	free(pixels);
	SDL_DestroyTexture(texture);
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();
}

void process_keyboard_input() {
	SDL_Event event;
	SDL_PollEvent(&event);

	// Keyboard interaction
	switch (event.type) {
	case SDL_QUIT: // when 'X' button is pressed in window titlebar
		// Exit program
		is_running = false;
		break;
	case SDL_KEYDOWN:
		switch (event.key.keysym.sym) {
		case SDLK_ESCAPE:
			// Exit program
			is_running = false;
			break;
		case SDLK_0:
			// Static display
			animation_mode = 0;
			break;
		case SDLK_1:
			// Animated display
			animation_mode = 1;
			break;
		// Also: SDLK_w, SDLK_a, SDLK_s, SDLK_d
		}
		break;
	}
}

void update_state() {
	// Clear frame buffer
	clear(0x000000FF);

	// Variable for camera movement
	if (animation_mode == 0) {
		camera_position.x = 0.0f;
		camera_position.y = 0.0f;
	}
	else if (animation_mode == 1) {
		float t = frame_index % 120;
		t = t / 60.0f;
		camera_position.x = sinf(t * M_PI);
		camera_position.y = cosf(t * M_PI);
	}

	// Draw a 5x5 rect at every projected point
	project_model();
	scale_projection();
	for (int i = 0; i < CUBE_POINT_COUNT; i++) {
		vec2_t pt = projected_points[i];
		int cx = pixels_w / 2;
		int cy = pixels_h / 2;
		uint32_t color = 0xFFFFFFFF; // white color
		draw_centered_rect(cx + (int)pt.x, cy + (int)pt.y, 5, 5, color);
	}

	// Update frame index
	frame_index++;
}

void run_render_pipeline() {
	// Render frame buffer
	SDL_UpdateTexture(texture, NULL, pixels, pixels_w * sizeof(uint32_t));
	SDL_RenderCopy(renderer, texture, NULL, &window_rect);
	SDL_RenderPresent(renderer);
}

int main(int argc, char* argv[]) {
	printf("Started program.\n");

	if (!initialize_windowing_system()) return 0;

	// Create the cube model
	build_cube_model();

	animation_mode = 0;

	// Game loop
	is_running = true;
	while (is_running) {
		process_keyboard_input();
		update_state();
		run_render_pipeline();
		SDL_Delay(1000 / 60); // Wait for 1/60 second = (1000 / 60)
	}

	clean_up_windowing_system();

	return 0;
}
