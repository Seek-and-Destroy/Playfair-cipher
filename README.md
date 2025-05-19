# Playfair-cipher


# Описание

Реализация шифра Плейфера на C++ с графическим интерфейсом на SFML. Программа позволяет:


        Вводить ключевое слово для создания матрицы 5x5.
        

        Вводить текст для шифрования или дешифрования.


        Выбирать режим: 1 для шифрования, 2 для дешифрования.


        Просматривать результат и матрицу 5x5.



# Требования


        Visual Studio 2022 с поддержкой C++.


        C++17.


        SFML 2.5+, настроенный в Visual Studio.


        Windows (для доступа к шрифту C:\Windows\Fonts\arial.ttf).





# Настройка SFML в Visual Studio

        1. Установите SFML для x64


        2. Настройте проект в Visual Studio (после открытия, см. ниже):
        
        
        Project -> Properties:
        

                C/C++ -> General -> Additional Include Directories: добавьте путь к SFML include


                Linker -> General -> Additional Library Directories: добавьте путь к SFML lib


                Linker -> Input -> Additional Dependencies: 

               
                        Debug: sfml-graphics-d.lib;sfml-window-d.lib;sfml-system-d.lib.

                        Release: sfml-graphics.lib;sfml-window.lib;sfml-system.lib.
                        


               Linker -> Advanced -> Entry Point:


                       Enter: mainCRTStartup

               
               
               Linker -> System ->  Subsystem:


                       Windows (/SUBSYSTEM:WINDOWS)
                
        3. Закинуть файлы из папки SFML-2.5.1\bin на ваш диск:\папка проекта\Playfair-cipher\Playfair-cipher\x64\Debug


# Использование



        1. После запуска откроется окно SFML.


        2. Введите ключевое слово (например, KEYWORD).


        3. Введите текст для обработки (например, HELLO WORLD).


        4. Нажмите 1 для шифрования или 2 для дешифрования.


        5. Просмотрите результат и матрицу 5x5.


        6. Нажмите Enter, чтобы начать заново.



# Структура проекта:


        // В разработке!

        
        main.cpp: Точка входа программы.
        
        
        
                        
        
                        
                
        
