## Git rules (Important)
- Khi làm việc hãy checkout nhánh mới từ nhánh main và làm việc trên nhánh đó
> git checkout -b branch_name <br/>
- Chỉ được push code lên nhánh **khác** nhánh main, sau đó tạo Pull Request vào nhánh main

## Install essential dependencies 
> sudo apt-get update <br/>
> sudo apt-get install libmysqlclient-dev libcjson-dev

## Fix makefile with error missing seperate
> perl -pi -e 's/^  */\t/' Makefile

## Hướng dẫn chạy backend
Đầu tiên để chạy được backend chúng ta phải setup database:
- Ở đây chúng ta sử dụng MySQL
- Điều chỉnh các tham số đến database trong file /backend/src/db/connect-db.c va backend/src/cli_migrate.c như hình dưới đây
![alt text](<Screenshot from 2024-12-02 19-54-40.png>)
- THứ tự các tham số: DB_HOST, DB_USERNAME, DB_PASS, DB_NAME (các tham số này tuỳ chúng ta tạo trong MySQL)
  
- Sau khi setup xong database thì chúng ta sẽ cần chạy migration để tự động tạo các tables trong mysql

> make <br/>
> make migrate

- Để chạy server chúng ta sử dụng lệnh
>  make run

## Cách test API server 
1. Cài netcat (Ubuntu)
> sudo apt-get install netcat
2. Sử dụng netcat để gửi 1 TCP request (Dưới đây là ví dụ test 1 API signup)
> echo -e "POST /signup\nContent-Type: application/json\n\n{\"email\":\"test@example.com\",\"password\":\"password123\",\"username\":\"testuser\"}" | nc localhost 8080