set serveroutput on size 32000
set linesize 300

/*--=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=--
	PROCEDURE #1
		pro_AvgGrade
=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=--*/
create or replace procedure pro_AvgGrade as
	/*	declarations	*/
	type numArr IS VARRAY(50) OF number; 

	avgGrades numArr;
	idSchools numArr;

	schoolCount number;
	minGrade number;
	maxGrade number;
	cnter number;

	binText varchar(255);
	binUnderText varchar(255);
	schoolName varchar(255);
	lineToPrint varchar(255);
begin
	-- get school count
	SELECT COUNT(SchoolId) INTO schoolCount FROM School;
	-- get average grade array
	SELECT AVG(Grade), SchoolId BULK COLLECT INTO avgGrades, idSchools FROM Student GROUP BY SchoolId;
	-- get min grade
	SELECT MIN(minyGradey) INTO minGrade
		FROM (SELECT MIN(Grade) AS minyGradey FROM Student GROUP BY SchoolId);
	-- get max grade
	SELECT MAX(maxyGradey) INTO maxGrade
		FROM (SELECT MAX(Grade) AS maxyGradey FROM Student GROUP BY SchoolId);

	minGrade := FLOOR(minGrade / 10) * 10;
	maxGrade := CEIL(maxGrade / 10) * 10 - 10;

	FOR i IN (minGrade / 10) .. ((maxGrade / 10) - 1) LOOP
		binText := binText || RPAD('>' || i*10 || ', <=' || (i+1)*10 || ' ', 15, ' ');
		binUnderText := binUnderText || RPAD('-', 11, '-') || '    ';
	END LOOP;

	dbms_output.put_line(RPAD('SCHOOLNAME', 27, ' ') || RPAD('AVGGRADE:', 17, ' ') || binText);
	dbms_output.put_line(RPAD('-', 22, '-') || '     ' || RPAD(' ', 17, ' ') || binUnderText);

	FOR i IN 1 .. idSchools.COUNT LOOP
		SELECT SchoolName INTO schoolName FROM School WHERE SchoolId = idSchools(i);
		lineToPrint := RPAD(schoolName, 27, ' ') || RPAD(' ', 17, ' ');


		cnter := minGrade + 10;
		WHILE avgGrades(i) > cnter
		LOOP
			cnter := cnter + 10;
			lineToPrint := lineToPrint || RPAD(' ', 15, ' ');
		END LOOP;

		lineToPrint := lineToPrint || '     x';

		dbms_output.put_line(lineToPrint);
		lineToPrint := '';
	END LOOP;
end;
/

/*	actually	run	the	procedure	*/
begin
pro_AvgGrade;
end;
/

/*--=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=--
	PROCEDURE #2
		pro_DispInternSummary
=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=--*/
create or replace procedure pro_DispInternSummary as
	/*	declarations	*/              
    medianNum number;
    outString varchar(255);
    maxInternships number;
    sumGoodStudents number;
    numStuds number;
    totalStuds number;

begin
    -- get max internships
    SELECT MAX(NumInternships) INTO maxInternships
    FROM 
       (SELECT COUNT(StudentId) as numStudents, NumInternships 
		FROM 
			(SELECT COUNT(StudentId) as numInternships, StudentId
			 FROM Internship
			  GROUP BY StudentId
			   ORDER BY numInternships ASC)
		GROUP BY NumInternships
        ORDER BY NumInternships ASC);
        
    -- get sum of good studs (for lazy stud caluclation later)
    SELECT SUM(numStudents) INTO sumGoodStudents
    FROM 
       (SELECT COUNT(StudentId) as numStudents, NumInternships 
		FROM 
			(SELECT COUNT(StudentId) as numInternships, StudentId
			 FROM Internship
			  GROUP BY StudentId
			   ORDER BY numInternships ASC)
		GROUP BY NumInternships
        ORDER BY NumInternships ASC);
        
    -- get total studs (for lazy stud caluclation later)
    SELECT COUNT(*) INTO totalStuds FROM STUDENT;

    -- get median #
    SELECT MEDIAN(numInternships) INTO medianNum
    FROM 
        (SELECT COUNT(Internship.StudentId) as numInternships
         FROM Internship RIGHT JOIN Student ON Internship.StudentId = Student.StudentId
          GROUP BY Student.StudentId
           ORDER BY numInternships ASC);


    -- printing
	dbms_output.put_line('numberOfInternships |	#student');

    -- calculate lazy studs
    dbms_output.put_line('0' || LPAD('|   ' || (totalStuds - sumGoodStudents), 24, ' '));
    
    -- do rest
   FOR i in 1..maxInternships
   LOOP
        BEGIN
            SELECT numStudents INTO numStuds
            FROM 
               (SELECT COUNT(StudentId) as numStudents, NumInternships 
                FROM 
                    (SELECT COUNT(StudentId) as numInternships, StudentId
                     FROM Internship
                      GROUP BY StudentId
                       ORDER BY numInternships ASC)
                GROUP BY NumInternships
                ORDER BY NumInternships ASC)
                WHERE NumInternships = i;
        EXCEPTION
            WHEN NO_DATA_FOUND THEN
                numStuds := 0;
        END;    
            outString := i || LPAD('|   ' || numStuds, 24, ' ');
       
            IF i = medianNum THEN
                outString := outString || ' <-- median';
            END IF;
            
            dbms_output.put_line(outString);
   END LOOP;

end;
/

/*	actually	run	the	procedure	*/
begin
pro_DispInternSummary;
end;
/

/*

SELECT MEDIAN(numInternships) as median 
FROM 
	(SELECT COUNT(Internship.StudentId) as numInternships
	 FROM Internship RIGHT JOIN Student ON Internship.StudentId = Student.StudentId
	  GROUP BY Student.StudentId
	   ORDER BY numInternships ASC);

SELECT MEDIAN(NumInternships) FROM
	(SELECT COUNT(StudentId) as numStudents, NumInternships 
	FROM 
		(SELECT COUNT(StudentId) as numInternships, StudentId
		 FROM Internship
		  GROUP BY StudentId
		   ORDER BY numInternships ASC)
	GROUP BY NumInternships);

*/


/*--=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=--
	PROCEDURE #3
		pro_AddIntern
=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=--*/
create or replace procedure pro_AddIntern(
StudentName_i IN STUDENT.STUDENTNAME%type, 
CompName_i IN COMPANY.COMPNAME%type, 
RecName_i IN RECRUITER.RECNAME%type, 
OfferYear_i IN INTERNSHIP.OFFERYEAR%type) as
	/*	declarations	*/
    sID STUDENT.STUDENTID%type;
    cID COMPANY.COMPID%type;
    rID RECRUITER.RECID%type;
    
begin
    
		SELECT studentId INTO sID
        FROM (STUDENT)
        WHERE STUDENT.studentName = StudentName_i AND ROWNUM = 1;
        
		SELECT compId INTO cID
        FROM (COMPANY)
        WHERE COMPANY.compName = CompName_i AND ROWNUM = 1;
        
		SELECT recId INTO rID
        FROM (RECRUITER)
        WHERE RECRUITER.recName = RecName_i AND ROWNUM = 1;

    BEGIN
        INSERT INTO INTERNSHIP VALUES (sID, cID, rID, OfferYear_i);
    EXCEPTION
        WHEN DUP_VAL_ON_INDEX THEN
            dbms_output.put_line('ERROR: internship already exists in db!');
    END;

end;
/

/*	actually	run	the	procedure	*/
begin
pro_AddIntern('student7', 'Comp2', 'Rec1', 2055);
end;
/


/*--=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=--
	PROCEDURE #4
		pro_DispCompany
=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=--*/
create or replace procedure pro_DispCompany as
	/*	declarations	*/
    cursor compList is
        SELECT * FROM Company ORDER BY CompName ASC;
        
	type strArr IS VARRAY(50) OF varchar(255); 

	schoolNames strArr;
        
    outString varchar(10000);
    nameString varChar(1000);
    numInterns number;
    boolInt number;
    avgNum number;
    
begin
    
        dbms_output.put_line(RPAD('CompanyName', 22, ' ') || 
                             RPAD('Address', 32, ' ') ||
                             RPAD('NumOfStudentInterns', 22, ' ') ||
                             RPAD('School', 32, ' ') ||
                             RPAD('AverageGrade', 22, ' '));
                             
        dbms_output.put_line(RPAD('-', 20, '-') || '  ' ||
                             RPAD('-', 30, '-') || '  ' ||
                             RPAD('-', 20, '-') || '  ' ||
                             RPAD('-', 30, '-') || '  ' ||
                             RPAD('-', 20, '-'));
                             
    FOR compRow in compList
    LOOP
        -- name
        outString := RPAD(compRow.compName, 22, ' ');
        -- address
        outString := outString || RPAD(compRow.address, 32, ' ');
        
        BEGIN
        
        -- numInterns
        SELECT COUNT(StudentID) INTO numInterns
        FROM INTERNSHIP
        WHERE CompId = compRow.CompId
        GROUP BY CompID;
        
        outString := outString || RPAD(numInterns, 22, ' ');
        
        -- schools (omfg)
        SELECT schoolName BULK COLLECT INTO schoolNames FROM (
            SELECT schoolName, COUNT(CompId) as numI FROM (
                SELECT CompId, Internship.StudentID, Student.SchoolId, School.schoolName
                FROM INTERNSHIP
                    LEFT JOIN Student ON Internship.StudentId = Student.StudentId
                    LEFT JOIN School ON Student.SchoolId = School.SchoolId
            ) WHERE CompId = compRow.CompId
            GROUP BY schoolId, schoolName
            ORDER BY numI DESC
            FETCH FIRST 1 ROW WITH TIES
        ) ORDER BY schoolName ASC;
        
        boolInt := 0;
        FOR i IN 1 .. schoolNames.COUNT LOOP
            if boolInt = 1 THEN
                nameString := nameString || '/' || schoolNames(i);
            ELSE 
                nameString := nameString || schoolNames(i);
                boolInt := 1;
            END IF;
        END LOOP;
        
        outString := outString || RPAD(nameString, 32, ' ');
        nameString := '';        

        -- lastly, the avg
        SELECT CAST(AVG(avgs) AS DECIMAL(10,2)) INTO avgNum FROM (
            SELECT AVG(Grade) as avgs
            FROM Student
                LEFT JOIN Internship ON Student.StudentId = Internship.StudentId
                LEFT JOIN Company ON Internship.CompId = Company.compId
            WHERE Internship.CompId = compRow.CompId
            GROUP BY Student.studentId
        );
        
        outString := outString || ROUND(avgNum / 20 - 1, 2);
        
        EXCEPTION
            WHEN NO_DATA_FOUND THEN
                outString := outString || '0';
        END;
        
        dbms_output.put_line(outString);
    END LOOP;

end;
/

/*	actually	run	the	procedure	*/
begin
pro_DispCompany();
end;
/



/*--=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=--
	PROCEDURE #5
		pro_SearchStudent
=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=--*/
create or replace procedure pro_SearchStudent(sID IN STUDENT.STUDENTID%type) as
	/*	declarations	*/
    sName varchar(1000);
    sSchoolName varchar(1000);
    sGrade number;
    outString varchar(2000);
    flag number;
    numShips number;
    numJobs number;
    
begin
    flag := 0;

    dbms_output.put_line('Enter Value for StudentID: ' || sID);
    
        dbms_output.put_line(RPAD('StudentId', 17, ' ') || 
                             RPAD('StudentName', 22, ' ') ||
                             RPAD('School', 22, ' ') ||
                             RPAD('Grade', 17, ' ') ||
                             RPAD('NumOfInternships', 22, ' ') ||
                             RPAD('NumOfJobApp', 22, ' '));
                             
        dbms_output.put_line(RPAD('-', 15, '-') || '  ' ||
                             RPAD('-', 20, '-') || '  ' ||
                             RPAD('-', 20, '-') || '  ' ||
                             RPAD('-', 15, '-') || '  ' ||
                             RPAD('-', 20, '-') || '  ' ||
                             RPAD('-', 20, '-'));
    
    BEGIN
        SELECT StudentName, SchoolName, Grade COLLECT INTO sName, sSchoolName, sGrade
        FROM STUDENT
            LEFT JOIN School ON Student.schoolId = School.schoolId
        WHERE StudentId = sID;
    EXCEPTION
        WHEN NO_DATA_FOUND THEN
            flag := 1;
    END;

    IF flag = 0 THEN
        outString := RPAD(sID, 17, ' ') || RPAD(sName, 22, ' ') || RPAD(sSchoolName, 22, ' ') || RPAD(ROUND(sGrade / 20 - 1, 2), 17, ' ');
        
        -- get # internships
        SELECT Count(StudentId) INTO numShips
        FROM Internship
        WHERE StudentId = sID
        GROUP BY StudentId;
        
        outString := outString || RPAD(numShips, 22, ' ');
        
        -- get # jobs
        SELECT Count(StudentId) INTO numJobs
        FROM JobApplication
        WHERE StudentId = sID
        GROUP BY StudentId;
        
        outString := outString || RPAD(numJobs, 22, ' ');
    END IF;
    
    dbms_output.put_line(outString);
    
end;
/

/*	actually	run	the	procedure	*/
begin
pro_SearchStudent(3);
end;
/
    
    
    
    
/*--=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=--
	PROCEDURE #6
		pro_SearchRecuiter
=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=--*/
create or replace procedure pro_SearchRecuiter(rName IN RECRUITER.RECNAME%type) as
	/*	declarations	*/
    rID number;

    cursor compTable is
        SELECT Company.CompId as cID, CompName, COUNT(Student.StudentId) as cnt
        FROM INTERNSHIP
            LEFT JOIN Company ON Internship.CompId = Company.CompId
            LEFT JOIN Student ON Internship.StudentId = Student.StudentId
        WHERE RecId = rID
        GROUP BY Company.CompId, CompName
        ORDER BY CompName ASC;
    
	type strArr IS VARRAY(50) OF varchar(255); 

	schoolNames strArr;
    outString varchar(2000);
    nameString varchar(1000);
    avgGrade number;
    
    flag number;
    boolInt number;
    
begin
    flag := 0;

    dbms_output.put_line('Enter Value for RecName: ' || rName);

    BEGIN
         SELECT recId INTO rID FROM Recruiter WHERE RecName = rName;
    EXCEPTION
        WHEN NO_DATA_FOUND THEN
            flag := 1;
    END;

    IF flag = 0 THEN
        dbms_output.put_line('RecID: ' || rID);
        dbms_output.put_line('RecName: ' || rName);
        
    
        -- get top school names
        SELECT schoolName BULK COLLECT INTO schoolNames FROM (
            SELECT schoolName, COUNT(RecId) as numI FROM (
                SELECT RecId, Internship.StudentID, Student.SchoolId, School.schoolName
                FROM INTERNSHIP
                    LEFT JOIN Student ON Internship.StudentId = Student.StudentId
                    LEFT JOIN School ON Student.SchoolId = School.SchoolId
            ) WHERE RecId = rID
            GROUP BY schoolId, schoolName
            ORDER BY numI DESC
            FETCH FIRST 1 ROW WITH TIES
        ) ORDER BY schoolName ASC;
        
        boolInt := 0;
        FOR i IN 1 .. schoolNames.COUNT LOOP
            if boolInt = 1 THEN
                nameString := nameString || '/' || schoolNames(i);
            ELSE 
                nameString := nameString || schoolNames(i);
                boolInt := 1;
            END IF;
        END LOOP;
        
        dbms_output.put_line('School with most interns: ' || nameString);

        dbms_output.put_line(RPAD('CompanyName', 22, ' ') || 
                             RPAD('NumberOfInterns', 22, ' ') ||
                             RPAD('AverageStudentGrade', 32, ' '));
                             
        dbms_output.put_line(RPAD('-', 20, '-') || '  ' ||
                             RPAD('-', 20, '-') || '  ' ||
                             RPAD('-', 30, '-'));
                             
        FOR compRow IN compTable
        LOOP
            outString := RPAD(compRow.CompName, 22, ' ') || RPAD(compRow.cnt, 22, ' ');
            
            SELECT CAST(AVG(Grade) AS DECIMAL(10,2)) INTO avgGrade FROM
                (
                SELECT DISTINCT StudentId
                FROM Internship
                WHERE RecId = rID AND CompId = compRow.cID
                ) nq LEFT JOIN Student ON nq.studentId = Student.StudentId;
            
            outString := outString || ROUND(avgGrade / 20 - 1, 2);
            
            dbms_output.put_line(outString);
        END LOOP;

        --dbms_output.put_line(outString);
    ELSE
        dbms_output.put_line('No recruiter with that name found.');
    END IF;
    
end;
/

/*	actually	run	the	procedure	*/
begin
pro_SearchRecuiter('Rec2');
end;
/

