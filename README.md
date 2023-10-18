# Rating_Prediction
Collaborative filtering is a technique used to make recommendations based on the preferences of similar users. In this code, the system reads in a training dataset train.csv and a test dataset test.csv. 
The training dataset is used to create a matrix of ratings given by users for different movies. 
The test dataset contains test cases for which the system needs to predict the ratings that a user would give to a movie. 
The system first reads the training dataset and stores the ratings in a map of maps called rating_data. The map is structured such that the keys are user IDs and the values are maps with movie IDs as keys and ratings as values. This structure allows for efficient retrieval of ratings for a given user and movie. Next, the system reads the test dataset and for each test case, it calculates the predicted rating for the given user and movie using the following steps: 
1-Find all users who have rated the movie. 
2-Calculate the similarity between the given user and each of these users using the Pearson correlation coefficient. 
3-Use the similarities and the ratings of the other users to predict the rating of the given user for the movie. 
4-The predicted ratings are written to a file submission.csv.
We used UBCF and we printed top 10 rated movies and users in our code. We got less than 1 rmse and our code managed to do this task less than 6 minutes in our systems. 
We used Pearson similarity instead of cosine similarity because of easier implementation and more efficient structure.
