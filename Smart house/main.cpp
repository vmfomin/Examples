/**
 * @file      main.cpp
 * @author    vmf0min (vlifom@yandex.ru)
 * @brief     Задача 5. Умный дом.
 * Надо разработать упрощённую модель умного дома для дачи. Есть несколько
 * датчиков: датчик температуры снаружи, датчик температуры внутри дома. В доме
 * расположен электронный “умный” щиток с автоматами. Каждый автомат отвечает за
 * включение и отключение определённых устройств или групп устройств. Первый
 * автомат - это отключение и включение питания всего дома, второй - основные
 * розетки дома, третий - свет внутри дома, четвёртый - наружный свет в саду,
 * пятый - отопление в помещении, шестой - отопление водопровода идущего из
 * скважины с насосом, шестой - кондиционер в помещении.
 * Есть несколько условий по включению/отключению техники в доме и вне его.
 * Как только температура снаружи падает ниже 0, надо включить систему обогрева
 * водопровода и отключить её, если температура снаружи поднялась выше
 * 5градусов.
 * Если на дворе вечер (время больше 16:00 и меньше 5:00 утра) и снаружи есть
 * какое-то движение, то необходимо включить садовое освещение. Если движения
 * нет или время не вечернее - света снаружи быть не должно.
 * При условии, что температура в помещении упала ниже 22 градусов, должно
 * включится отопление. Как только температура поднимается выше или равно 25-и
 * градусам, отопление автоматически отключается.
 * Если температура в помещении поднялась до 30 градусов, включается
 * кондиционер. Как только температура становится 25 градусов - кондиционер
 * отключается.
 * Всё освещение в доме также “умное” и поддерживает настройку цветовой
 * температуры для комфортного нахождения. Каждый день начиная с 16:00 и до
 * 20:00, температура цвета должна плавно изменяться с 5000K до 2700К.
 * Разумеется, это изменение должно происходить в случае, если свет сейчас
 * включен. В 0:00 температура сбрасывается до 5000К.
 * Все события по отключению и включению устройств должны выводится в консоль
 * явным образом. Если устройство не изменило своего состояния (осталось
 * включенным или выключенным) события генерироваться не должно! Если свет в
 * доме включен, должна отображаться текущая цветовая температура.
 * Программа выполняется следующим образом. Каждый час пользователь сообщает
 * состояние всех основных датчиков и света: температура снаружи, температура
 * внутри, есть ли движение снаружи, включен ли свет в доме. Данные параметры
 * вводятся разом в одну строку, через пробел, а потом парсятся в переменные из
 * строкового буфера stringstream. Информация о движении выводится в формате
 * yes/no. Включение и отключение света происходит с помощью on/off. Стартовое
 * время для симуляции умного дома - это 0:00. Требуется осуществить симуляцию
 * на протяжении двух дней.
 * @version   0.1
 * @date      10-03-2021
 * @copyright Copyright (c) 2021
 */

#include <iostream>
#include <sstream>

enum Panel {
  POWER = 1 << 0,
  OUTLETS = 1 << 1,
  LIGHT_INSIDE = 1 << 2,
  LIGHT_GARDEN = 1 << 3,
  HEATING_INSIDE = 1 << 4,
  HEATING_WATERPIPE = 1 << 5,
  CONDITIONER = 1 << 6,
};

/**
 * @brief     Print the current status
 * @param     status        electrical panel status
 * @param     hour          current hour.
 */
void printStatus(const int16_t status, const int16_t hour);

int main() {
  std::cout << "\x1b[2J";
  char status{};  // current status of panel
  for (int16_t timeSimulation{}; timeSimulation < 48; ++timeSimulation) {
    int16_t currentHour = timeSimulation % 24;
    std::cout << "Current hour:\t" << currentHour << std::endl;
    std::cout << "Enter status:\x1b[32m\t";
    std::string textStatus{};
    std::getline(std::cin, textStatus);
    std::cout << "\x1b[0m";

    std::stringstream statusPanel{};
    statusPanel << textStatus;

    double temperatureOutside{};
    double temperatureInside{};
    std::string movingOutside{};
    std::string lightInside{};
    statusPanel >> temperatureOutside;
    statusPanel >> temperatureInside;
    statusPanel >> movingOutside;
    statusPanel >> lightInside;

    if (!(status & POWER)) status |= (POWER | OUTLETS);

    if (temperatureOutside < 0)
      status |= HEATING_WATERPIPE;
    else if ((status & HEATING_WATERPIPE) && temperatureOutside > 5)
      status &= ~HEATING_WATERPIPE;

    if (temperatureInside < 22)
      status |= HEATING_INSIDE;
    else if ((status & HEATING_INSIDE) && temperatureInside >= 25)
      status &= ~HEATING_INSIDE;

    if (temperatureInside >= 30)
      status |= CONDITIONER;
    else if ((status & CONDITIONER) && temperatureInside <= 25)
      status &= ~CONDITIONER;

    if ("yes" == movingOutside && (currentHour > 16 || currentHour < 5))
      status |= LIGHT_GARDEN;
    else if (status & LIGHT_GARDEN)
      status &= ~LIGHT_GARDEN;

    if ("on" == lightInside)
      status |= LIGHT_INSIDE;
    else if (status & LIGHT_INSIDE)
      status &= ~LIGHT_INSIDE;

    printStatus(status, currentHour);
  }

  std::cout
      << "\x1b[36mThe simulation is complete. All sensors are off.\nYou can "
         "live in this house\x1b[0m\n\n";
  status = 0;
  printStatus(status, 0);

  std::cout << std::endl;
  return 0;
}

void printStatus(const int16_t status, const int16_t hour) {
  std::string currentStatus{"\x1b[36mCurrent status:\x1b[0m\n"};
  if (status & POWER)
    currentStatus += "POWER:   \x1b[32mon\x1b[0m\n";
  else
    currentStatus += "POWER:   off\n";

  if (status & OUTLETS)
    currentStatus += "OUTLETS: \x1b[32mon\x1b[0m\n";
  else
    currentStatus += "OUTLETS: off\n";

  if (status & LIGHT_INSIDE) {
    int16_t lightTemperature{5000};
    if (hour >= 16 && hour < 20)
      lightTemperature -= (hour - 15) * 460;
    else if (hour >= 20 && hour <= 23)
      lightTemperature = 2700;
    currentStatus += "LIGHT_INSIDE: \x1b[32m" +
                     std::to_string(lightTemperature) + "\x1b[0m\n";
  } else {
    currentStatus += "LIGHT_INSIDE: off\n";
  }

  if (status & LIGHT_GARDEN)
    currentStatus += "LIGHT_GARDEN: \x1b[32mon\x1b[0m\n";
  else
    currentStatus += "LIGHT_GARDEN: off\n";

  if (status & HEATING_INSIDE)
    currentStatus += "HEATING_INSIDE:    \x1b[32mon\x1b[0m\n";
  else
    currentStatus += "HEATING_INSIDE:    off\n";

  if (status & HEATING_WATERPIPE)
    currentStatus += "HEATING_WATERPIPE: \x1b[32mon\x1b[0m\n";
  else
    currentStatus += "HEATING_WATERPIPE: off\n";

  if (status & CONDITIONER)
    currentStatus += "CONDITIONER: \x1b[32mon\x1b[0m\n";
  else
    currentStatus += "CONDITIONER: off\n";

  std::cout << currentStatus << std::endl;
}
