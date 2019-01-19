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
    pros::lcd::print(3, "                                                                                           ");
    pros::lcd::print(4, "                                                                                           ");
    pros::lcd::print(5, "                                                                                           ");
    pros::lcd::print(6, "                                                                                           ");
    pros::lcd::print(7, "                                                                                           ");
  }
  else if (page == SENSOR_VALUES) {
    pros::lcd::print(0, "SENSOR VALUES");
    pros::lcd::print(1, "cat_pot : [%d]", cat_pot.get_value());
		pros::lcd::print(2, "cBar position : [%d]", cBar.get_position());
		pros::lcd::print(3, "flipper : [%d]", flipper.get_position());
		pros::lcd::print(4, "gyro val :[%4.0f]", gyro.get_value());
		pros::lcd::print(5, "drive encoder value : [%d]", chassis.right_pos());
    pros::lcd::print(5, "<< AUTO SELECTION || MOTOR TEMPS >>");
    pros::lcd::print(6, "                                                                                           ");
    pros::lcd::print(7, "                                                                                           ");
  }
  else if (page == MOTOR_TEMPS) {
    pros::lcd::print(0, "MOTOR TEMPURATURES");
    pros::lcd::print(1, "catapult : [%2.0f]", cat.get_temperature());
    pros::lcd::print(2, "intake : [%2.0f]", intake.get_temperature());
    pros::lcd::print(3, "flipper : [%2.0f]", flipper.get_temperature());
    pros::lcd::print(4, "chainbar : [%2.0f]", cBar.get_temperature());
    pros::lcd::print(5, "average left drive : [%2.0f]", (drive_LF.get_temperature() + drive_LB.get_temperature())/2);
    pros::lcd::print(6, "average right drive : [%2.0f]", (drive_RF.get_temperature() + drive_RB.get_temperature())/2);
    pros::lcd::print(7, "<< SENSOR VALUES || AUTO SELECTION >>");
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
