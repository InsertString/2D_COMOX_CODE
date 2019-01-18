#include "main.h"
#include "robot_includes/robot_includes.h"

std::string auto_names[5] {
  "FLAG RED",
  "FLAG BLUE",
  "PARK RED",
  "PARK BLUE",
  "SKILLS"
};

int selected_auto;

int page;

int curr_lcd_btn_val;
int last_lcd_btn_val;


//~~~~~~~~~~~~~~~~~~~~~~~LCD~BUTTONS~~~~~~~~~~~~~~~~~~~~~~~~~~~//

//function that returns which lcd button is pressed//
int LCD_btn()
{
  return pros::lcd::read_buttons();
}

//function that returns 1 when the left LCD button is pressed//
int LCD_left_pressed()
{
  if (LCD_btn() == LCD_BTN_LEFT && curr_lcd_btn_val != last_lcd_btn_val)
    return 1;
  else
    return 0;
}

//function that returns 1 when the right LCD button is pressed//
int LCD_right_pressed()
{
  if (LCD_btn() == LCD_BTN_RIGHT && curr_lcd_btn_val != last_lcd_btn_val)
    return 1;
  else
    return 0;
}

//function that returns 1 when the center LCD button is pressed//
int LCD_center_pressed()
{
  if (LCD_btn() == LCD_BTN_CENTER && curr_lcd_btn_val != last_lcd_btn_val)
    return 1;
  else
    return 0;
}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~//




void lcd_control() {
  curr_lcd_btn_val = LCD_btn();

  if (page == AUTO_SELECT) {
    pros::lcd::print(0, "AUTONOMOUS SELECTION");
    pros::lcd::print(1, "AUTO : [%s]", auto_names[selected_auto]);
    pros::lcd::print(2, "<< MOTOR TEMPS || SENSOR VALUES >>");
  }
  else if (page == SENSOR_VALUES) {
    pros::lcd::print(0, "SENSOR VALUES");

    pros::lcd::print(5, "<< AUTO SELECTION || MOTOR TEMPS >>");
  }
  else if (page == MOTOR_TEMPS) {
    pros::lcd::print(0, "MOTOR TEMPURATURES");

    pros::lcd::print(9, "<< SENSOR VALUES || AUTO SELECTION >>");
  }

  if (LCD_left_pressed()) {
    if (page < 2)
      page++;
    else
      page = 0;
  }
  else if (LCD_center_pressed()) {
    if (selected_auto < 4)
      selected_auto++;
    else
      selected_auto = 0;
  }
  else if (LCD_right_pressed()) {
    if (page > 0)
      page--;
    else
      page = 2;
  }

  last_lcd_btn_val = curr_lcd_btn_val;
}
