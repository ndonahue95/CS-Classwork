------ Query 1
SELECT SchoolName, ROUND(AVG(COALESCE(Grade, 0)), 2) AS AverageGrade 
FROM (SELECT * FROM Student WHERE Student.Grade >= 60) Student
  RIGHT OUTER JOIN School ON (Student.SchoolId = School.SchoolId)
  GROUP BY SchoolName
  ORDER BY AverageGrade DESC;


------ Query 2
SELECT Student.StudentID, Student.StudentName, 
  (SELECT COUNT(*) FROM Internship WHERE Student.StudentID = Internship.StudentID) AS NumOfInternships
FROM Student
WHERE BirthDate = (SELECT MIN(BirthDate) FROM Student)
ORDER BY StudentName;


------ Query 3
SELECT Student.StudentID, Student.StudentName, 
  (SELECT COUNT(DISTINCT Job.CompId) FROM JobApplication
    LEFT JOIN Job ON JobApplication.JobID = Job.JobID
    LEFT JOIN Company ON Job.CompID = Company.CompID
    WHERE JobApplication.StudentID = Student.StudentID) AS NumOfCompanies
FROM Student
ORDER BY StudentName;


------ Query 4
SELECT CompName, numJobs as NumberOfJobs
FROM (
        SELECT Company.CompName, COALESCE(numJobs, 0) as numJobs
        FROM 
          (
            SELECT CompName, SUM(Job.JobNum) AS numJobs
            FROM Job 
            JOIN Company 
            ON Job.CompId = Company.CompId
            WHERE Job.CompId = Company.CompId AND Job.OfferYear >= 2014 AND Job.OfferYear <= 2016
            GROUP BY Company.CompName
          ) nestedq
        RIGHT JOIN Company ON nestedq.CompName = Company.CompName
      )
WHERE numJobs = (
                 SELECT MAX(numJobs) 
                 FROM (
                        SELECT Company.CompName, COALESCE(numJobs, 0) as numJobs
                        FROM 
                          (
                            SELECT CompName, SUM(Job.JobNum) AS numJobs
                            FROM Job 
                            JOIN Company 
                            ON Job.CompId = Company.CompId
                            WHERE Job.CompId = Company.CompId AND Job.OfferYear >= 2014 AND Job.OfferYear <= 2016
                            GROUP BY Company.CompName
                          ) nestedq
                        RIGHT JOIN Company ON nestedq.CompName = Company.CompName
                      )
                )
ORDER BY CompName;


------ Query 5
SELECT *
FROM (
          SELECT CompName, numJobs as NumberOfJobs
          FROM (
                  SELECT Company.CompName, COALESCE(numJobs, 0) as numJobs
                  FROM 
                    (
                      SELECT CompName, SUM(Job.JobNum) AS numJobs
                      FROM Job 
                      JOIN Company 
                      ON Job.CompId = Company.CompId
                      WHERE Job.CompId = Company.CompId AND Job.OfferYear >= 2014 AND Job.OfferYear <= 2016
                      GROUP BY Company.CompName
                    ) nestedq
                  RIGHT JOIN Company ON nestedq.CompName = Company.CompName
                )
          ORDER BY NumberOfJobs
          FETCH FIRST 3 ROWS WITH TIES
        )
ORDER BY CompName;


------ Query 6
SELECT CompName, numJobs AS NumOfJobs, NumOfInternships
FROM (
        SELECT Company.CompName, COALESCE(numJobs, 0) as numJobs
        FROM 
          (
            SELECT CompName, SUM(Job.JobNum) AS numJobs
            FROM Job 
            JOIN Company 
            ON Job.CompId = Company.CompId
            WHERE Job.CompId = Company.CompId AND Job.OfferYear >= 2014 AND Job.OfferYear <= 2016
            GROUP BY Company.CompName
          ) nestedq
        RIGHT JOIN Company ON nestedq.CompName = Company.CompName
      ) aaa
  RIGHT JOIN (
              SELECT CompName as bCompName, COALESCE(NumOfInternships, 0) AS NumOfInternships
              FROM (
                      SELECT CompId, COUNT(CompID) as NumOfInternships
                      FROM Internship
                      GROUP BY CompId
                    ) nestedq
                RIGHT JOIN Company ON nestedq.CompId = Company.CompId
            ) bbb ON aaa.CompName = bbb.bCompName
ORDER BY NumOfJobs DESC;


------ Query 7
SELECT Student.StudentId, 
  StudentName,
  TRUNC(MONTHS_BETWEEN(SYSDATE, BirthDate)/12) AS Age,
  COALESCE(numI, 0) as NumOfInernships
FROM Student
  LEFT JOIN School ON Student.SchoolId = School.SchoolId
  LEFT JOIN (
              SELECT StudentId, COUNT(StudentId) AS numI
              FROM Internship
              GROUP BY StudentId
            ) nestedq
  ON nestedq.StudentId = Student.StudentId
WHERE UPPER(SchoolName) = 'PURDUE'
ORDER BY StudentName;


------ Query 8
SELECT RecId, RecName, count AS NumOfCompanies
FROM Recruiter
  LEFT JOIN (
                SELECT RecId as RecId2, COUNT(DISTINCT CompId) as count
                FROM Internship
                GROUP BY RecId
            ) foo ON Recruiter.RecId = foo.RecId2
WHERE count >= 2
ORDER BY RecName;


------ Query 9
SELECT JobNum, JobTitle, Salary, CompName, COALESCE(count,0) AS NumOfStudents
FROM Job
  LEFT JOIN Company ON Job.CompId = Company.CompId
  LEFT JOIN (
              SELECT JobId, COUNT(StudentId) as count
              FROM JobApplication
              GROUP BY JobId
            ) nestedq ON Job.JobId = nestedq.JobId
WHERE OfferYear = 2017
ORDER BY JobNum, JobTitle;


------ Query 10
SELECT SchoolName, COUNT(Grade) AS FailedCount 
FROM (SELECT * FROM Student WHERE Student.Grade < 60) Student
  RIGHT OUTER JOIN School ON (Student.SchoolId = School.SchoolId)
GROUP BY SchoolName
ORDER BY SchoolName;




