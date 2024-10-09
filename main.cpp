#include <iostream>
#include <iomanip>
#include <numeric>
#include <string>
#include <vector>

using namespace std;

class ManagerEBR {
// в полях класса, в аргументах функций и в самих функциях, на мой взгляд,
// целесообразнее в место int использовать либо unsigned int, либо size_t, так как
// а) id и кол-во страниц может быть только положительным,
// б) мы избавляемся от ворнингов при обращении к эдементам vector по индексам
// в) при  необходимости можем на входе сразу сделать проверку на корректность входных параметров  
    vector<int> number_page_user_;
    vector<int> count_users_on_page_;
    vector<int> all_users_;

public:
    ManagerEBR(){
// 100001 и 1001 выглядят как магические числа
//целессобразно, на мой взгляд, их сделать константными глобальными переменными  
        number_page_user_.resize(100001);
        count_users_on_page_.resize(1001);
    }

    void ReadUserPage(int user_id, int page){
        int currentPage = number_page_user_[user_id];
        if( (currentPage < page) && (currentPage > 0)){
            --count_users_on_page_[currentPage];
        }else{
            all_users_.push_back(user_id);
        }

        number_page_user_[user_id] = page;
        ++count_users_on_page_[page];
    }

    double CheerUser(int user_id){
        if(all_users_.size() == 1 && all_users_[0] == user_id)
            return 1;

        if(number_page_user_[user_id] == 0)
            return 0;

        auto beg = count_users_on_page_.begin();
        auto end = beg + number_page_user_[user_id];

        int fewerPeopleRead = accumulate(beg, end, 0);
        return fewerPeopleRead / static_cast<double>(all_users_.size() - 1);
    }
};

int main()
{
    ManagerEBR manager;
    int countRequests;
// для удобства тестирования я бы вынес считывание запросов в функцию
// что бы была возможность не только считывать из cin, но и из других потоков,
// например из файла
    cin >> countRequests;
    for(int i = 0; i < countRequests; ++i){
        string typeStr;
        cin >> typeStr;
// при осуществлении парсинга в main мы лишаемся возможности провести его тестирования
// на мой субъективный взгляд целесообразней вынести это в отдельную функцию
// именно по этому в своём решении я это и реализовал
        if(typeStr == "READ"){
            int userId, page;
            cin >> userId >> page;
            manager.ReadUserPage(userId, page);
        }else if(typeStr == "CHEER"){
            int userId;
            cin >> userId;
            cout << setprecision(6) << manager.CheerUser(userId) << endl;
        }else continue;
    }
}
