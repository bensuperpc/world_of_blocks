#include "player.hpp"

player::player(gameContext &game_context_ref) : _game_context_ref(game_context_ref) {
  player_logger = std::make_unique<LoggerDecorator>("player", "player.log");
  Camera _camera = {0};
  _camera.position = (Vector3){48.0f, 48.0f, -48.0f};
  _camera.target = (Vector3){-28.0f, 48.0f, -28.0f};
  _camera.up = (Vector3){0.0f, 1.0f, 0.0f};
  _camera.fovy = 80.0f;
  _camera.projection = CAMERA_PERSPECTIVE;

  this->camera = _camera;
  DisableCursor();
}

Vector3 player::get_position() const { return this->camera.position; }

player::~player() {}

void player::updateGameInput() {
  closest_collision = {0};
  closest_collision.hit = false;
  closest_collision.distance = std::numeric_limits<float>::max();
  if (closest_block != nullptr) {
  }
  collisions.clear();

  ray = GetMouseRay(_game_context_ref.screen_middle, camera);

  float player_speed = 0.5f;
  float zoom = GetMouseWheelMove() * 0.5f;
  Vector3 movement = {0.0f, 0.0f, 0.0f};
  Vector3 rotation = {0.0f, 0.0f, 0.0f};

  if (IsKeyPressed(KEY_F5)) {
    auto date = std::time(nullptr);
    std::stringstream ss;
    ss << std::put_time(std::localtime(&date), "%Y-%m-%d_%H-%M-%S");
    std::string filename = ss.str();
    player_logger->info("Taking screenshot: {}", filename);
    TakeScreenshot(("screenshot_" + filename + ".png").c_str());
  }

  if (IsKeyDown(KEY_W) || IsKeyDown(KEY_UP)) {
    movement.x = player_speed;
  }
  if (IsKeyDown(KEY_S) || IsKeyDown(KEY_DOWN)) {
    movement.x = -player_speed;
  }
  if (IsKeyDown(KEY_D) || IsKeyDown(KEY_RIGHT)) {
    movement.y = player_speed;
  }
  if (IsKeyDown(KEY_A) || IsKeyDown(KEY_LEFT)) {
    movement.y = -player_speed;
  }
  if (IsKeyDown(KEY_SPACE)) {
    movement.z = player_speed;
  }
  if (IsKeyDown(KEY_LEFT_SHIFT)) {
    movement.z = -player_speed;
  }

  rotation.x = GetMouseDelta().x * 0.05f;
  rotation.y = GetMouseDelta().y * 0.05f;

  UpdateCameraPro(&camera, movement, rotation, zoom);

  // Update player Chunk position in game context
  _game_context_ref.player_chunk_pos = std::move(Chunk::get_chunk_position(camera.position));
  _game_context_ref.player_pos = std::move(camera.position);
}

void player::updateGameLogic() {}

void player::updateOpenglLogic() {}

void player::updateDraw2d() {
  // Draw crosshair in the middle of the screen
  DrawLine(_game_context_ref.screen_middle.x - 10, _game_context_ref.screen_middle.y, _game_context_ref.screen_middle.x + 10, _game_context_ref.screen_middle.y,
           SKYBLUE);
  DrawLine(_game_context_ref.screen_middle.x, _game_context_ref.screen_middle.y - 10, _game_context_ref.screen_middle.x, _game_context_ref.screen_middle.y + 10,
           SKYBLUE);
}

void player::updateDraw3d() {}

void player::updateDrawInterface() {}
