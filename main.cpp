#include <iostream>
#include <iomanip>
#include <numeric>
#include <string>
#include <vector>

using namespace std;

class ManagerEBR {
    vector<int> number_page_user_;
    vector<int> count_users_on_page_;
    vector<int> all_users_;

public:
    ManagerEBR(){
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
    cin >> countRequests;
    for(int i = 0; i < countRequests; ++i){
        string typeStr;
        cin >> typeStr;

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
