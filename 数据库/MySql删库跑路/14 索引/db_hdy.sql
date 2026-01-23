/*
 Navicat Premium Dump SQL

 Source Server         : hdy_chat
 Source Server Type    : MySQL
 Source Server Version : 80403 (8.4.3)
 Source Host           : localhost:3306
 Source Schema         : db_hdy

 Target Server Type    : MySQL
 Target Server Version : 80403 (8.4.3)
 File Encoding         : 65001

 Date: 07/01/2026 16:08:39
*/

SET NAMES utf8mb4;
SET FOREIGN_KEY_CHECKS = 0;
set global log_bin_trust_function_creators=1;	

DROP DATABASE IF EXISTS db_hdy;
CREATE DATABASE db_hdy; 
USE db_hdy;

-- ----------------------------
-- Table structure for course
-- ----------------------------
DROP TABLE IF EXISTS `course`;
CREATE TABLE `course`  (
  `id` int NOT NULL AUTO_INCREMENT,
  `course_id` int NOT NULL,
  `course_name` varchar(40) CHARACTER SET utf8mb3 COLLATE utf8mb3_general_ci NULL DEFAULT NULL,
  PRIMARY KEY (`id`) USING BTREE
) ENGINE = InnoDB AUTO_INCREMENT = 1 CHARACTER SET = utf8mb3 COLLATE = utf8mb3_general_ci COMMENT = '课程表' ROW_FORMAT = Dynamic;

-- ----------------------------
-- Table structure for student_info
-- ----------------------------
DROP TABLE IF EXISTS `student_info`;
CREATE TABLE `student_info`  (
  `id` int NOT NULL AUTO_INCREMENT,
  `student_id` int NOT NULL,
  `name` varchar(20) CHARACTER SET utf8mb3 COLLATE utf8mb3_general_ci NULL DEFAULT NULL,
  `course_id` int NOT NULL,
  `class_id` int NULL DEFAULT NULL,
  `create_time` datetime NULL DEFAULT CURRENT_TIMESTAMP ON UPDATE CURRENT_TIMESTAMP,
  PRIMARY KEY (`id`) USING BTREE
) ENGINE = InnoDB AUTO_INCREMENT = 1 CHARACTER SET = utf8mb3 COLLATE = utf8mb3_general_ci COMMENT = '学生表' ROW_FORMAT = Dynamic;

-- ----------------------------
-- Procedure structure for insert_course
-- ----------------------------
DROP PROCEDURE IF EXISTS `insert_course`;
delimiter ;;
CREATE PROCEDURE `insert_course`(max_num INT)
  COMMENT '随机插入课程表存储过程'
BEGIN
	DECLARE i INT DEFAULT 0;
	SET autocommit = 0;	#设置手动提交事务
	REPEAT #循环
	SET i = i + 1; #赋值
	INSERT INTO course (course_id, course_name ) VALUES (1000+i,rand_string(6));
	UNTIL i = max_num
	END REPEAT;
	COMMIT; #提交事务
END
;;
delimiter ;

-- ----------------------------
-- Procedure structure for insert_stu
-- ----------------------------
DROP PROCEDURE IF EXISTS `insert_stu`;
delimiter ;;
CREATE PROCEDURE `insert_stu`(max_num INT)
  COMMENT '随机插入学生信息表存储过程'
BEGIN
	DECLARE i INT DEFAULT 0;
  DECLARE course_count INT DEFAULT 0;
  -- 查询课程表记录数
  SELECT COUNT(*) INTO course_count FROM course;
  -- 循环插入数据
	SET autocommit = 0;	#设置手动提交事务
	REPEAT #循环
    SET i = i + 1; #赋值
    INSERT INTO student_info (course_id, class_id ,student_id ,NAME ) 
    VALUES (rand_num(1000,1000 + course_count),rand_num(10000,10200),1000000+i,rand_string(6));
	UNTIL i = max_num 
  END REPEAT;
	COMMIT; #提交事务
END
;;
delimiter ;

-- ----------------------------
-- Function structure for rand_num
-- ----------------------------
DROP FUNCTION IF EXISTS `rand_num`;
delimiter ;;
CREATE FUNCTION `rand_num`(from_num INT ,to_num INT)
 RETURNS int
  COMMENT '随机生成数字串数函数'
BEGIN
	DECLARE i INT DEFAULT 0;
	SET i = FLOOR(from_num + RAND()*(to_num - from_num + 1))	; 
	RETURN i;
END
;;
delimiter ;

-- ----------------------------
-- Function structure for rand_string
-- ----------------------------
DROP FUNCTION IF EXISTS `rand_string`;
delimiter ;;
CREATE FUNCTION `rand_string`(n INT)
 RETURNS varchar(255) CHARSET utf8mb4
  COMMENT '随机生成字符串数函数'
BEGIN
	DECLARE chars_str VARCHAR(100) DEFAULT'abcdefghijklmnopqrstuvwxyzABCDEFJHIJKLMNOPQRSTUVWXYZ'; 
	DECLARE return_str VARCHAR(255) DEFAULT '';
	DECLARE i INT DEFAULT 0; 
	WHILE i < n DO
		SET return_str =CONCAT(return_str,SUBSTRING(chars_str,FLOOR(1+RAND()*52),1)); 			
		SET i = i + 1;
	END WHILE;
	RETURN return_str; 
END
;;
delimiter ;

SET FOREIGN_KEY_CHECKS = 1;
set global log_bin_trust_function_creators=0;	
