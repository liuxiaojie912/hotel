#!/bin/bash

#确认存储数据的位置
user_date="/home/liu/hotel/script/user_date.txt"            #输入的数据位置（在文件的里面）

#主页面
function homepage(){
	clear
	echo ">>hotel management<<"
	echo "1. 输入用户记录"
       	echo "2. 浏览全部用户记录"
   	echo "3. 按照idcard查找用户记录"
    	echo "4. 按照idcard删除用户记录"
    	echo "5. 按照idcard修改用户记录"
	echo -n "   选择你要进行的操作    "
}

#输入用户记录
function input(){
	while true; do
	echo "输入用户信息"
	echo -n "输入7位用户ID:"
	read newuser_ID

	echo -n "输入用户姓名:"
	read newuser_name

	echo -n "请输入进店人数:"
	read newuser_num
	
	echo -n "请输入用户的房间名:"
	read newuser_room

	#用户的信息保存到文件里面去
	echo "$newuser_ID,$newuser_name,$newuser_num,$newuser_room" >> "$user_date"
	#判断用户是否继续输入
	echo "用户信息输入完成"
	echo -n "是否继续输入用户信息（Y/N）："
	read answer
	
	if [[ ! "$answer" =~ ^[Yy]$ ]]; then
		break
	fi
done
}




#显示所有的用户记录
function view_all(){
	if [ ! -f "$user_date" ] || [ ! -s "$user_date" ]; then
		echo "您还没有输入用户"
		return
	fi
	
	echo "ID          用户名      人数       房间号"
		cat "$user_date" | while IFS=',' read -r user_ID user_name user_num user_room; do
        		printf "%-12s %-12s %-10s %-12s\n" "$user_ID" "$user_name" "$user_num" "$user_room"
		done
	
}

#查询用户记录
function search(){
	if [ ! -f "$user_date" ] || [ ! -s "$user_date" ]; then
                echo "您还没有输入用户"
                return
        fi
	
	echo -n "请输入您想查询的ID:"
        read newuser_ID
        result=$( grep "^$newuser_ID," "$user_date" )
        if [[ -n "$result" ]]; then
		echo "$result" | awk -F ',' '{printf "ID: %s\n姓名: %s\n人数: %s\n房间号: %s\n", $1, $2, $3, $4}'
	else
		echo "没有此ID，请返回重新输入"
	fi
}

#删除用户记录
function delete(){
	 if [ ! -f "$user_date" ] || [ ! -s "$user_date" ]; then
                echo "您还没有输入用户"
                return
        fi
        
        echo -n"请输入您想查询的ID:"
        read newuser_ID
        result=$( grep "^$newuser_ID," "$user_date" )
        if [[ -n "$result" ]]; then
		grep -q "^$user_ID," "$user_date" > "$user_date.tmp"
		mv "$user_date.tmp" "$user_date"
		echo "用户记录已删除"
	else
		echo "没有此ID，请查询后再删除"
	fi
}

#更改用户记录
function change(){
	if [ ! -f "$user_date" ] || [ ! -s "$user_date" ]; then
                echo "您还没有输入用户"
                return
        fi

        echo -n "请输入您想查询的ID"
        read newuser_ID
        result=$( grep "^$newuser_ID," "$user_date" )
        if [[ -n "$result" ]]; then
		echo -n "请输入新的ID："
		read ID

		echo -n "请输入新的用户名："
		read name

		echo -n "请输入新的人数:"
		read num

		echo -n "请输入新的房间号:"
		read room
		
		new_user = "$ID,$name,$num,$room"
		sed -i " s/^$newuser_ID,.*/$new_user/ " "$user_date"
		echo "用户记录已更改"
	else
		echo"没有此ID，请查询后再更改"
	fi
}

while true ; do
	homepage
	read choice
	case $choice in
		1) input ;;
		2) view_all ;;
		3) search ;;
		4) delete ;;
		5) change ;;
		*) echo "输入有误，请重新输入" ;;
	esac

	echo -n "按回车键继续"
	read
done

















