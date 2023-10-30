USE games;
-- 第一题：求出目前总积分最高的系名及其积分。
	-- 1.确定所需要的数据表
	-- spoeter：系名
	-- grade：积分
	-- 2.确定已知关联字段
	-- 远动员和积分：sporter.sporterno=grade.sporterno
#常规写法
SELECT s.deptname,SUM( g.mark ) 总分 
FROM sporter s,grade g 
WHERE s.sporterno = g.sporterno 
GROUP BY deptname 
HAVING 总分 =(
		WITH temp AS (
		SELECT s.deptname,SUM( g.mark ) totalmark 
		FROM sporter s,grade g 
		WHERE s.sporterno = g.sporterno 
		GROUP BY deptname 
		) 
		SELECT MAX( totalmark ) totalmark 
	  FROM temp 
	);
#优化之后的写法	
WITH temp AS (
SELECT s.deptname deptname,SUM( g.mark ) totalmark 
FROM sporter s,grade g 
WHERE s.sporterno = g.sporterno 
GROUP BY deptname 
)
SELECT deptname,totalmark FROM temp 
HAVING totalmark =(SELECT MAX(totalmark) FROM temp);	
	
-- 第二题：找出在一操场进行比赛的各项目名称极其冠军的姓名。
	-- 确定所需数据表
		#sporter:冠军的姓名
		#item：一操场比赛的运动员
		#grade：求出冠军
	-- 确定关联字段
		#运动员和积分：sporter.sporterno=grade.sporterno
		#项目和积分：item.itemno = grade.itemno	
WITH 
	temp AS(
		SELECT i.itemno ,MAX(g.mark) maxmark
		FROM item i,grade g
		WHERE i.itemno=g.itemno AND i.loc='一操场'
		GROUP BY i.itemno
				)#求一操场每个项目最高分
SELECT * 
FROM item i,temp t,sporter s,grade g
WHERE i.itemno= t.itemno AND s.sporterno=g.sporterno
AND t.itemno=g.itemno AND g.mark=t.maxmark;



-- 第三题：找出参加了莫影所参加过的项目的其他同学的姓名。
	-- 确定所需数据表
		#sporter：莫影
		#grade：莫影参加过的项目
WITH temp AS(		
SELECT itemno FROM grade g,sporter s
WHERE g.sporterno=s.sporterno		
AND s.name='莫影')

SELECT DISTINCT s.name
FROM  sporter s,grade g
WHERE s.sporterno=g.sporterno
AND g.itemno in (SELECT * FROM temp) AND s.name <> '莫影';

-- 第四题：经查莫影因为使用了违禁药品，其成绩都记为0分，请在数据库中做出相应的修改。
UPDATE grade SET mark=0 WHERE sporterno=(
SELECT sporterno FROM sporter WHERE name='莫影');

-- 第五题：经组委会协商，需要删除女子跳高比赛项目。
DELETE FROM item WHERE itemname='女子跳高';


	-- 先删除fk_itemno外键约束
ALTER TABLE grade DROP FOREIGN KEY fk_itemno;	
	-- 重新添加fk_itemno外键约束
ALTER TABLE grade ADD CONSTRAINT fk_itemno FOREIGN KEY(itemno) REFERENCES item(itemno) ON UPDATE CASCADE ON DELETE CASCADE;

SHOW INDEX FROM grade;
