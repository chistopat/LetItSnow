#include <array>
#include <iostream>

#include <thread>

using namespace std::chrono_literals;
using namespace std::string_literals;

class Canvas {
 public:
  enum class Color {
    F_BLACK = 30,
    F_RED = 31,
    F_GREEN = 32,
    F_YELLOW = 33,
    F_BLUE = 34,
    F_MAGENTA = 35,
    F_CYAN = 36,
    F_WHITE = 37,
    B_BLACK = 40,
    B_RED = 41,
    B_GREEN = 42,
    B_YELLOW = 44,
    B_BLUE = 44,
    B_MAGENTA = 45,
    B_CYAN = 46,
    B_WHITE = 47
  };

 public:
  static constexpr auto kDefaultWidth  = 80;
  static constexpr auto kDefaultHeight = 25;

 public:
  explicit Canvas(std::ostream& out, int width = kDefaultWidth, int height = kDefaultHeight)
      : out_(out), width_(width), height_(height), cursor_({0,0}) {
    Clear();
    out_ << kEsc << kVisibleCursor;
  }

  void Home() {
    cursor_.x = 0;
    cursor_.y = 0;

    out_ << kEsc << kHome;
  }

  void SetColor(Color color) {
    out_ << kEsc << '[' << static_cast<int>(color) << 'm';
  }

  void ResetColor() {
    out_ << kEsc << kResetColor;
  }

  void Clear() {
      out_ << kEsc << kClear;
  };

  void MoveCursor(int x, int y) {
    cursor_.x = x;
    cursor_.y = y;

    out_ << kEsc << '[' << y << ';' << x << "H";
  }

  template<typename T>
  void Draw(T data) {
    out_ << data;
  }

 private:
  struct Cursor {
    int x;
    int y;
  };

 private:
  static constexpr auto kEsc = "\033";
  static constexpr auto kHome = "[H";
  static constexpr auto kClear = "[2J";
  static constexpr auto kResetColor = "[0m";
  static constexpr auto kVisibleCursor = "[?251";

 private:
  std::ostream& out_;
  int width_;
  int height_;
  Cursor cursor_;
};

#define clrscr() printf(ESC "[2J")//lear the screen, move to (1,1)
#define gotoxy(x, y) printf(ESC "[%d;%dH", y, x);
#define visible_cursor() printf(ESC "");
//Set Display Attribute Mode	<ESC>[{attr1};...;{attrn}m
#define resetcolor() printf(ESC "[0m")

int main() {
  auto canvas = Canvas(std::cout, 80, 25);
  std::this_thread::sleep_for(500ms);
  canvas.MoveCursor(10, 10);
  std::this_thread::sleep_for(500ms);

  canvas.SetColor(Canvas::Color::F_MAGENTA);
  std::this_thread::sleep_for(500ms);

  canvas.Draw("let it snow");
  std::this_thread::sleep_for(500ms);
  canvas.ResetColor();
  std::this_thread::sleep_for(500ms);
  canvas.Home();
  std::this_thread::sleep_for(500ms);
  canvas.Draw("text");
}
