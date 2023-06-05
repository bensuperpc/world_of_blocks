#ifndef WORLD_OF_CUBE_GAME_CLASS_HPP
#define WORLD_OF_CUBE_GAME_CLASS_HPP

class game_class {
    public:
        virtual ~game_class() = default;
        game_class() = default;

        virtual void update() = 0;
        virtual void draw2d() = 0;
        virtual void draw3d() = 0;
};

#endif  // WORLD_OF_CUBE_GAME_CLASS_HPP