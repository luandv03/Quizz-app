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