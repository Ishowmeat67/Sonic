----- STUDENT TABLE (CREATE)
DROP TABLE IF EXISTS Student;
CREATE TABLE Student (
    StudentID INT PRIMARY KEY,
    Student_Name VARCHAR(100) NOT NULL,
    DateOfBirth DATE NOT NULL,
    Age INT NULL,
    Gender VARCHAR(10),
    Street_Address VARCHAR(100),
    Post_Code VARCHAR(10),
    City VARCHAR(50),
    State VARCHAR(50),
    Country VARCHAR(50),
    Department_ID VARCHAR(100),
    FOREIGN KEY (Department_ID) REFERENCES Department(Department_ID) ON DELETE CASCADE 
    
);

INSERT INTO Student (StudentID, Student_Name, DateOfBirth, Gender, Street_Address, Post_Code, City, State, Country,Department_ID)
VALUES 
(1, 'Shong Qien Buo', '2007-08-10', 'Male', '56, Bandar Bukit Tinggi 2, Lorong Batu Nilam 33A', '41299', 'Klang', 'Selangor', 'Malaysia','DIPBUSS'),
(2, 'Irwin Tan', '2007-01-02', 'Male', '89, Bandar Bukit Bayu, Lorong Batu Nilam 22B', '32440', 'Subang', 'Terengganu', 'Malaysia','DIPCOMM'),
(3, 'Calvine Joash', '2007-05-29', 'Male', '34, Bandar Setia Alam, Lorong 44H', '45666', 'Puchong', 'Perak', 'Malaysia','DIPENGR'),
(4, 'Wong Yu Herng', '2007-08-11', 'Male', '66, Bandar Bukit Kepong, Lorong 67D', '56789', 'Kuala Lumpur', 'Perlis', 'Malaysia','DIPHOSP'),
(5, 'Qandeel Asif', '2006-11-06', 'Female', '99, Bandar Bukit Raja, Lorong Batu Nilam 29F', '41430', 'Cheras', 'Negeri Sembilan', 'Malaysia','DIPXDCS');

SELECT * FROM Student;





-- ContactNumber Table (CREATE)
DROP TABLE IF EXISTS ContactNumber;
CREATE TABLE ContactNumber (
    StudentID INT NOT NULL,
    Phone_Number VARCHAR(20) NOT NULL,
    PRIMARY KEY (StudentID, Phone_Number),
    FOREIGN KEY (StudentID) REFERENCES Student(StudentID) ON DELETE CASCADE
);

INSERT INTO ContactNumber (StudentID, Phone_Number)
VALUES 
(001, '012376-5581'),
(002, '016662-5348'),
(002, '012661-6181'),
(003, '012377-0583'),
(004, '012966-3996'),
(005, '014678-9877');

SELECT * FROM ContactNumber;





-- EmailAddresss Table (CREATE)
DROP TABLE IF EXISTS EmailAddress;
CREATE TABLE EmailAddress (
    StudentID INT NOT NULL,
    Email VARCHAR(100),
    PRIMARY KEY (StudentID, Email),
    FOREIGN KEY (StudentID) REFERENCES Student(StudentID) ON DELETE CASCADE
);

INSERT INTO EmailAddress (StudentID, Email)
VALUES 
(001, 'jaspershong2006@gmail.com'),
(001, 'M44100768@student.uow.edu.my'),
(002, 'irwin67@gmail.com'),
(003, 'calvine88@gmail.com'),
(004, 'wong23@hotmail.com'),
(005, 'asif123@gmail.com');




-- READ ----
-- 1.
SELECT StudentID,Student_Name
FROM Student
WHERE StudentID = 1;
-- 2.
SELECT s.Student_Name, ea.Email
FROM Student s
JOIN EmailAddress ea ON s.StudentID = ea.StudentID
ORDER BY Student_Name ASC;
-- 3.
SELECT 
    s.Student_Name, 
    cn.Phone_Number, 
    ea.Email
FROM Student s
LEFT JOIN ContactNumber cn ON s.StudentID = cn.StudentID
LEFT JOIN EmailAddress ea ON s.StudentID = ea.StudentID
WHERE s.StudentID = 3;


-- UPDATE ---
-- 1.
UPDATE Student
SET Street_Address = '12, Jalan Flora, Lorong Batu Nilam 67',
    City = 'Shah Alam',
    Post_Code = '40000'
WHERE StudentID = 1;
-- 2.
UPDATE EmailAddress
SET Email = 'shong_new2026@gmail.com'
WHERE StudentID = 1 AND Email = 'jaspershong2006@gmail.com';


-- DELETE ----
-- 1.
DELETE FROM EmailAddress
WHERE StudentID = 1 AND Email = 'jaspershong2006@gmail.com';
-- 2.
DELETE FROM Student 
WHERE StudentID = 3;









-- Course Table (CREATE)
CREATE TABLE Course (
    Course_Code VARCHAR(10) PRIMARY KEY,
    Course_Name VARCHAR(100) NOT NULL,
    Credits INT,
    Fee DECIMAL(10, 2),
    Department_ID VARCHAR(100),
    Room_Number VARCHAR(10),
    Lecturer_ID VARCHAR(10),
    FOREIGN KEY (Department_ID) REFERENCES Department(Department_ID),
    FOREIGN KEY (Room_Number) REFERENCES Classroom(Room_Number),
    FOREIGN KEY (Lecturer_ID) REFERENCES Lecturer(Lecturer_ID)
);

INSERT INTO Course (Course_Code, Course_Name, Credits, Fee,Department_ID,Room_Number,Lecturer_ID)
VALUES ('BUSS1013', 'Principles Of Marketing', 3, 900.00,'DIPBUSS','R001','L001'),
       ('COMM2014', 'Mass Communication Theory', 2, 500.00,'DIPCOMM','R002','L002'),
	   ('ENGR1014', 'Introduction to Mechanical Engineering', 3, 1250.00,'DIPENGR','R003','L003'),
       ('HOSP1023', 'Introduction to Hospitality', 2, 950.00,'DIPHOSP','R004','L004'),
       ('XDCS1054N', 'Database Systems', 4, 1200.00,'DIPXDCS','R005','L005');
       
SELECT * FROM Course;

-- READ ---
-- 1.
SELECT *
FROM Course
WHERE Course_Code = 'COMM2014';
-- 2.
SELECT COUNT(*) AS Total_Courses
FROM Course;

-- UPDATE ---
-- 1.
UPDATE Course
SET Course_Name = 'Principles Of Management',
    Course_Code = 'BUSS2013',
    Credits = 4,
    Fee = 1350.00
WHERE Course_Code = 'BUSS2013';
-- 2.
UPDATE Course
SET Fee = Fee * 0.80
WHERE Course_Code = 'ENGR1014';


-- DELETE ---
-- 1.
DELETE FROM Course
WHERE Credits < 3;
-- 2.
DELETE FROM Course
WHERE Course_Code IN ('ENGR1014', 'XDCS1054N');




-- Department Table (CREATE)
CREATE TABLE Department (
    Department_ID VARCHAR(10) PRIMARY KEY,
    Department_name VARCHAR(100) NOT NULL,
    Office_Location VARCHAR(100) NOT NULL
);

INSERT INTO Department (Department_ID, Department_name, Office_Location)
VALUES
('DIPBUSS', 'School Of Business', 'Block A'),
('DIPCOMM', 'School Of Communication', 'Block B'),
('DIPENGR', 'School Of Engineering', 'Block C'),
('DIPHOSP', 'School Of Hospitality', 'Block D'),
('DIPXDCS', 'School Of Computer Science', 'Block E');

SELECT * FROM Department;

-- READ ---
-- 1.
SELECT * 
FROM Department
WHERE Department_ID = 'DIPBUSS';
-- 2.
SELECT s.Student_name, d.Department_name
FROM Student s
JOIN Department d 
ON s.Department_ID = d.Department_ID
WHERE d.department_name = 'School of Business';


-- UPDATE ---
-- 1.
UPDATE Department
SET Office_Location = 'Block C'
WHERE Department_ID = 'DIPBUSS';
-- 2.
UPDATE Department
SET department_name = 'School of Engineering Technology'
WHERE Department_ID = 'DIPENGR';


-- DELETE ---
-- 1.
DELETE FROM Department
WHERE Department_ID = 'DIPCOMM';
-- 2.
DELETE FROM Department
WHERE department_name = 'School of Hospitality'
AND Office_Location = 'Block D';


-- Enrolment Table (CREATE)
DROP TABLE IF EXISTS Enrolment;
CREATE TABLE Enrolment (
    StudentID INT,
    Course_Code VARCHAR(10),
    Enrolment_Date DATE,
    Status VARCHAR(20),
    FOREIGN KEY (StudentID) REFERENCES Student(StudentID),
    FOREIGN KEY (Course_Code) REFERENCES Course(Course_Code)
    ON DELETE CASCADE
);

INSERT INTO Enrolment (StudentID, Course_Code, Enrolment_Date, Status)
VALUES ( 1,'BUSS2013','2026-03-20','ACTIVE'),
	   ( 2,'COMM2014','2025-04-12','ACTIVE'),
	   ( 3,'ENGR1014','2024-02-16','ACTIVE'),
       (4,'HOSP1023','2026-09-24','ACTIVE'),
       (5,'XDCS1054N','2026-04-01','PENDING');

SELECT * FROM Enrolment;


-- READ ---
-- 1.
SELECT * FROM Enrolment;
-- 2.
SELECT 
    s.Student_Name,
    s.StudentID,
    c.Course_Name,
    e.Enrolment_Date,
    e.Status,
    d.Department_Name
FROM Enrolment e
JOIN Student s ON e.StudentID = s.StudentID
JOIN Course c ON e.Course_Code = c.Course_Code
JOIN Department d ON s.Department_ID = d.Department_ID;



-- UPDATE ---
-- 1.
UPDATE Enrolment
SET Status = 'ACTIVE'
WHERE StudentID = 5;
-- 2.
UPDATE Enrolment
SET Enrolment_Date = '2020-06-07'
WHERE StudentID = 2;



-- DELETE ---
-- 1.
DELETE FROM Enrolment
WHERE StudentID = 3;
-- 2.
DELETE FROM Enrolment
WHERE Status = 'Pending';

-- ADVANCED SQL OBJECT
-- 1.VIEW
-- 1.
DROP VIEW IF EXISTS StudentDepartmentView;
CREATE VIEW StudentDepartmentView AS
SELECT s.StudentID, s.Student_name,s.Gender, d.Department_name,d.Department_ID
FROM Student s
JOIN Department d
ON s.Department_ID = d.Department_ID;

SELECT * FROM StudentDepartmentView;



-- 2. Stored Procedure
-- 1.
DELIMITER //

CREATE PROCEDURE UpdateCourseDetails(
    IN courseCode VARCHAR(10),
    IN newRoom VARCHAR(10),
    IN newFee DECIMAL(10,2)
)
BEGIN
    UPDATE Course
    SET Room_Number = newRoom,
        Fee = newFee
    WHERE Course_Code = courseCode;
END //

DELIMITER ;

CALL UpdateCourseDetails('COMM2014', 'R004',1000.00);

-- 2.
DELIMITER //

CREATE PROCEDURE AddNewStudent(
    IN p_studentid VARCHAR(10),
    IN p_name VARCHAR(100),
    IN p_dob DATE,
    IN p_gender VARCHAR(10),
    IN p_street_address VARCHAR(100),
    IN p_post_code VARCHAR(10),
    IN p_city VARCHAR(50),
    IN p_state VARCHAR(50),
    IN p_country VARCHAR(50),
    IN p_dept_id VARCHAR(10)
)
BEGIN
    INSERT INTO Student 
    (StudentID, Student_Name, DateOfBirth, Gender, 
     Street_Address, Post_Code, City, State, Country, Department_ID)
    
    VALUES 
    (p_studentid, p_name, p_dob, p_gender,
     p_street_address, p_post_code, p_city, p_state, p_country, p_dept_id);
END //

DELIMITER ;

CALL AddNewStudent(
    6,
    'Sheva Amir',
    '2005-07-20',
    'Female',
    '67,Bandar Puchong,Lorong 67C',
    '42345',
    'Klang',
    'Selangor',
    'Malaysia',
    'DIPCOMM'
);

-- 3.TRIGGER
-- 1.
DELIMITER //

CREATE TRIGGER ValidateCourseFee
BEFORE INSERT ON Course
FOR EACH ROW
BEGIN
    IF NEW.fee < 100 THEN
        SIGNAL SQLSTATE '45000'
        SET MESSAGE_TEXT = 'Course fee must be at least 100';
    END IF;
END //

DELIMITER ;


-- 4.Function
-- 1. 
DELIMITER //

CREATE FUNCTION CalculateDiscountedFee(
    originalFee DECIMAL(10,2),
    discountPercent DECIMAL(5,2)
)
RETURNS DECIMAL(10,2)
DETERMINISTIC
BEGIN
    DECLARE discountedFee DECIMAL(10,2);
    
    SET discountedFee = originalFee - (originalFee * discountPercent / 100);
    
    RETURN discountedFee;
END //

DELIMITER ;

SELECT 
    Course_Code,
    Course_Name,
    CONCAT(20,'%') AS Discount_Percentage,
    Fee AS Original_Fee,
    CalculateDiscountedFee(fee, 20) AS Discounted_Price
FROM Course
WHERE Course_Code = 'COMM2014';

SHOW DATABASES;
SHOW TABLES;

---------------------------------------------------------------------------------------------------------------------------





























-- ALTER TABLE Course
-- ADD COLUMN Room_Number VARCHAR(10),
-- ADD COLUMN Lecturer_ID VARCHAR(10);
-- ALTER TABLE Course
-- RENAME COLUMN Course_Name TO Name;
-- ALTER TABLE Course
-- RENAME COLUMN Name TO Course_Name;
-- ALTER TABLE Course
-- RENAME COLUMN DeptID TO Department_ID;
-- ALTER TABLE Course
-- ADD CONSTRAINT fk_course_classroom
-- FOREIGN KEY (Room_Number)
-- REFERENCES Classroom(Room_Number);
-- ALTER TABLE Course
-- ADD CONSTRAINT fk_course_department
-- FOREIGN KEY (Department_ID)
-- REFERENCES Department(Department_ID);
-- ALTER TABLE Course
-- ADD CONSTRAINT fk_course_lecturer
-- FOREIGN KEY (Lecturer_ID)
-- REFERENCES Lecturer(Lecturer_ID);

CREATE TABLE Classroom(
Room_Number VARCHAR(10) PRIMARY KEY,
Capacity INT NOT NULL,
Floor VARCHAR(10));


INSERT INTO Classroom (Room_Number, Capacity, Floor)
VALUES
('R001', 40, '1A'),
('R002', 35, '2A'),
('R003', 50, '2A'),
('R004', 45, 3),
('R005', 60, '4B');

SELECT * FROM Classroom;

ALTER TABLE Classroom
ADD COLUMN Capacity INT NOT NULL,
ADD COLUMN Floor VARCHAR(10);




CREATE TABLE Lecturer(
Lecturer_ID VARCHAR(10) PRIMARY KEY);
DROP TABLE Classroom;

INSERT INTO Lecturer (Lecturer_ID, lecturer_name, specialization)
VALUES
('L001', 'Mr. Ahmad',  'Marketing'),
('L002', 'Mr. Lim',  'Mass Communication'),
('L003', 'Mr. Tan',  'Mechanical Engineering'),
('L004', 'Mr. Wong', 'Hospitality Management'),
('L005', 'Ms. Lee', 'Software Engineering');
SELECT * FROM Lecturer;
DELETE FROM Lecturer;



DELETE FROM Department;
SELECT * FROM Department;

ALTER TABLE Lecturer
ADD COLUMN Lecturer_Name VARCHAR(100) NOT NULL,
ADD COLUMN Specialization VARCHAR(100);

ALTER TABLE Course
ADD DeptID INT ;
ALTER TABLE Course
MODIFY DeptID VARCHAR(100);
ALTER TABLE Course
ADD CONSTRAINT fk_department
FOREIGN KEY (DeptID) REFERENCES Department(DeptID);


DELETE FROM Course;

SHOW TABLES;

SELECT *
FROM Course
WHERE Course_Code = 'COMM2014';

SELECT COUNT(*) AS Total_Courses
FROM Course; 

UPDATE Course
SET Course_Name = 'Principles Of Management' ,
 Course_Code ='BUSS2013',
 Credits = 4,
 Fee = 1350.00
WHERE Course_Code = 'BUSS1013';


UPDATE Course
SET Fee = Fee * 0.80 
WHERE Course_Code ='ENGR1014';

DELETE FROM Course
WHERE Credits < 3;

DELETE FROM Course
WHERE Course_Code IN ('ENGR1014', 'XDCS1054N');



UPDATE Course
SET Course_Code = 'BUSS1013'
WHERE Course_Name = 'Principles Of Marketing';
UPDATE Course
SET Course_Name = 'Mass Communication Theory'
WHERE Course_Code = 'MPU2163';
UPDATE Course
SET Course_Code = 'COMM2014'
WHERE Course_Name =  'Mass Communication Theory';
UPDATE Course
SET Course_Name =  'Introduction to Hospitality'
WHERE Course_Code = 'XDCS2034';
UPDATE Course
SET Course_Code = 'HOSP1023'
WHERE Course_Name = 'Introduction to Hospitality';
UPDATE Course
SET Course_Name = 'Introduction to Engineering'
WHERE Course_Code ='XDCS1013';
UPDATE Course
SET Course_Code ='ENGR1014'
WHERE Course_Name = 'Introduction to Engineering';
UPDATE Course
SET Fee = '1250.00'
WHERE Course_Code = 'ENGR1014';
UPDATE Course
SET Fee = '950.00'
WHERE Course_Code = 'HOSP1023';



SELECT * FROM Student s, Course c
ORDER BY s.StudentID , c.Fee ASC;


UPDATE EmailAddress SET StudentID = 1 WHERE StudentID = 001;
UPDATE EmailAddress SET StudentID = 2 WHERE StudentID = 002;
UPDATE EmailAddress SET StudentID = 3 WHERE StudentID = 003;
UPDATE EmailAddress SET StudentID = 4 WHERE StudentID = 004;
UPDATE EmailAddress SET StudentID = 5 WHERE StudentID = 005;

SELECT * FROM Student;
SELECT * FROM EmailAddress;
SELECT * FROM ContactNumber;

SELECT StudentID,Student_Name
FROM Student
WHERE StudentID = 1;

SELECT s.Student_Name, ea.Email
FROM Student s
JOIN EmailAddress ea ON s.StudentID = ea.StudentID
ORDER BY Student_Name ASC;

SELECT 
    s.Student_Name, 
    cn.Phone_Number, 
    ea.Email
    FROM Student s
LEFT JOIN ContactNumber cn ON s.StudentID = cn.StudentID
LEFT JOIN EmailAddress ea ON s.StudentID = ea.StudentID
WHERE s.StudentID = 3;


UPDATE Student
SET Street_Address = '12, Jalan Flora, Lorong Batu Nilam 67', 
    City = 'Shah Alam', 
    Post_Code = '40000'
WHERE StudentID = 1;
UPDATE Student
SET Student_Name = 'Irwin Tan'
WHERE StudentID = 2;
UPDATE EmailAddress
SET Email = 'shong_new2026@gmail.com'
WHERE StudentID = 1 AND Email = 'jaspershong2006@gmail.com';
UPDATE EmailAddress
SET Email = 'jaspershong2006@gmail.com'
WHERE StudentID = 1 AND Email = 'shong_new2026@gmail.com' ;

DELETE FROM EmailAddress
WHERE StudentID = 1 AND Email = 'jaspershong2006@gmail.com';
DELETE FROM Student 
WHERE StudentID = 3;








DROP VIEW StudentDepartmentView;
SELECT * FROM Course;
DROP PROCEDURE AddNewStudent;
DELETE FROM Enrolment;

























