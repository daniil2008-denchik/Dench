#include <SDL2/SDL.h>
#include <cmath>        
#include <iostream>     
#include <string>       
#include <memory>       
#include <stdexcept>    

namespace Constants {

    constexpr int SCREEN_WIDTH  = 800;      
    constexpr int SCREEN_HEIGHT = 600;      
    
    
    constexpr int BALL_RADIUS   = 20;       
    
    constexpr float GRAVITY     = 0.15f;    
    constexpr float BOOST       = 1.08f;    
    constexpr float MAX_SPEED   = 30.0f;    
    
    constexpr int FPS           = 60;       
    constexpr int FRAME_DELAY   = 1000 / FPS; 
    
    
    namespace Color {
        constexpr Uint8 BLACK_R = 0;        
        constexpr Uint8 BLACK_G = 0;        
        constexpr Uint8 BLACK_B = 0;        
        
        constexpr Uint8 WHITE_R = 255;      
        constexpr Uint8 WHITE_G = 255;   
        constexpr Uint8 WHITE_B = 255;      
        
        constexpr Uint8 ALPHA_OPAQUE = 255; 
    }
}

class Ball {
private:
    float x_;   
    float y_;   
    float vx_;  
    float vy_;  
    
public:

    Ball(float start_x, float start_y, float start_vx, float start_vy) noexcept
        : x_(start_x), y_(start_y), vx_(start_vx), vy_(start_vy) {}
    
    float getX() const noexcept { return x_; }
    float getY() const noexcept { return y_; }
    
    void update() noexcept {
        
        vy_ += Constants::GRAVITY;
        
        
        x_ += vx_;
        y_ += vy_;
        
        
        checkCollisions();
        

        clampSpeed();
    }
    
private:
    
    void checkCollisions() noexcept {
    
        if (x_ + Constants::BALL_RADIUS > Constants::SCREEN_WIDTH) {
            x_ = Constants::SCREEN_WIDTH - Constants::BALL_RADIUS;
            vx_ *= -Constants::BOOST;
        }
        

        if (x_ - Constants::BALL_RADIUS < 0) {
            x_ = Constants::BALL_RADIUS;
            vx_ *= -Constants::BOOST;
        }
        
        
        if (y_ + Constants::BALL_RADIUS > Constants::SCREEN_HEIGHT) {
            y_ = Constants::SCREEN_HEIGHT - Constants::BALL_RADIUS;
            vy_ *= -Constants::BOOST;
            vx_ *= Constants::BOOST;  
        }
        

        if (y_ - Constants::BALL_RADIUS < 0) {
            y_ = Constants::BALL_RADIUS;
            vy_ *= -Constants::BOOST;
        }
    }
    
    void clampSpeed() noexcept {

        if (vx_ > Constants::MAX_SPEED)  vx_ = Constants::MAX_SPEED;
        if (vx_ < -Constants::MAX_SPEED) vx_ = -Constants::MAX_SPEED;
        
        // По Y
        if (vy_ > Constants::MAX_SPEED)  vy_ = Constants::MAX_SPEED;
        if (vy_ < -Constants::MAX_SPEED) vy_ = -Constants::MAX_SPEED;
    }
}

class SDLRenderer {
private:
    SDL_Renderer* renderer_;
    
public:
    
    SDLRenderer(SDL_Window* window) 
        : renderer_(SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC)) {
        if (!renderer_) {
            throw std::runtime_error("Failed to create renderer: " + std::string(SDL_GetError()));
        }
    }
    
    
    ~SDLRenderer() {
        if (renderer_) {
            SDL_DestroyRenderer(renderer_);
        }
    }
    
    
    SDLRenderer(const SDLRenderer&) = delete;
    SDLRenderer& operator=(const SDLRenderer&) = delete;
    
    SDLRenderer(SDLRenderer&& other) noexcept : renderer_(other.renderer_) {
        other.renderer_ = nullptr;
    }
    
    SDLRenderer& operator=(SDLRenderer&& other) noexcept {
        if (this != &other) {
            if (renderer_) SDL_DestroyRenderer(renderer_);
            renderer_ = other.renderer_;
            other.renderer_ = nullptr;
        }
        return *this;
    }
    
    
    SDL_Renderer* get() const noexcept { return renderer_; }
    
    operator SDL_Renderer*() const noexcept { return renderer_; }
};

class SDLWindow {
private:
    SDL_Window* window_;
public:
    
    SDLWindow(const char* title, int width, int height)
        : window_(SDL_CreateWindow(
            title,
            SDL_WINDOWPOS_CENTERED,
            SDL_WINDOWPOS_CENTERED,
            width,
            height,
            0)) {
        if (!window_) {
            throw std::runtime_error("Failed to create window: " + std::string(SDL_GetError()));
        }
    }
    

    ~SDLWindow() {
        if (window_) {
            SDL_DestroyWindow(window_);
        }
    }
    
    
    SDLWindow(const SDLWindow&) = delete;
    SDLWindow& operator=(const SDLWindow&) = delete;
    

    SDLWindow(SDLWindow&& other) noexcept : window_(other.window_) {
        other.window_ = nullptr;
    }
    
    SDLWindow& operator=(SDLWindow&& other) noexcept {
        if (this != &other) {
            if (window_) SDL_DestroyWindow(window_);
            window_ = other.window_;
            other.window_ = nullptr;
        }
        return *this;
    }
    
    
    SDL_Window* get() const noexcept { return window_; }
    
    
    operator SDL_Window*() const noexcept { return window_; }
};


class SDLGuard {
public:
    SDLGuard(Uint32 flags) {
        if (SDL_Init(flags) != 0) {
            throw std::runtime_error("SDL_Init failed: " + std::string(SDL_GetError()));
        }
    }
    
    ~SDLGuard() {
        SDL_Quit();
    }
    

    SDLGuard(const SDLGuard&) = delete;
    SDLGuard& operator=(const SDLGuard&) = delete;
};


void drawCircle(SDL_Renderer* renderer, int cx, int cy, int radius) noexcept {
    
    for (int dy = -radius; dy <= radius; ++dy) {
    
        int dx = static_cast<int>(std::sqrt(static_cast<float>(radius * radius - dy * dy)));
        

        SDL_RenderDrawLine(renderer, cx - dx, cy + dy, cx + dx, cy + dy);
    }
}


bool handleEvents() noexcept {
    SDL_Event event;
    while (SDL_PollEvent(&event)) {
        switch (event.type) {
            case SDL_QUIT:
                return false;  
                
            case SDL_KEYDOWN:
                if (event.key.keysym.sym == SDLK_ESCAPE) {
                    return false;  
                }
                break;
                
            
            default:
                break;
        }
    }
    return true;  
}


void renderFrame(SDL_Renderer* renderer, const Ball& ball) noexcept {
    
    SDL_SetRenderDrawColor(renderer, 
        Constants::Color::BLACK_R,
        Constants::Color::BLACK_G,
        Constants::Color::BLACK_B,
        Constants::Color::ALPHA_OPAQUE);
    SDL_RenderClear(renderer);
    
    
    SDL_SetRenderDrawColor(renderer,
        Constants::Color::WHITE_R,
        Constants::Color::WHITE_G,
        Constants::Color::WHITE_B,
        Constants::Color::ALPHA_OPAQUE);
    
    drawCircle(renderer, 
        static_cast<int>(ball.getX()), 
        static_cast<int>(ball.getY()), 
        Constants::BALL_RADIUS);
    
    
    SDL_RenderPresent(renderer);
}


int main(int argc, char* argv[]) {
    
    (void)argc;
    (void)argv;
    
    try {
        
        SDLGuard sdl(SDL_INIT_VIDEO);
        

        SDLWindow window("Ball Simulation (C++17 + SDL2)", 
                        Constants::SCREEN_WIDTH, 
                        Constants::SCREEN_HEIGHT);
        
        SDLRenderer renderer(window);
        
        
        Ball ball(
            Constants::SCREEN_WIDTH / 2.0f,  
            100.0f,                        
            3.5f,                             
            0.0f                               
        );
        
        
        bool running = true;
        Uint32 frameStart;
        int frameTime;
        
        while (running) {
            frameStart = SDL_GetTicks();
            
            
            running = handleEvents();
            
            
            ball.update();
renderFrame(renderer, ball);
            
            
            frameTime = SDL_GetTicks() - frameStart;
            if (Constants::FRAME_DELAY > frameTime) {
                SDL_Delay(Constants::FRAME_DELAY - frameTime);
            }
        }
        
    } catch (const std::exception& e) {
        
        std::cerr << "Error: " << e.what() << std::endl;
        return 1;
    }
    
    
    return 0;
}
