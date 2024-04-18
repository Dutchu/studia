import cv2
import numpy as np

# Define the function to filter the background
def filter_background(frame, tol):
    avg_color_per_row = np.average(frame, axis=0)
    avg_color = np.average(avg_color_per_row, axis=0)
    diff = np.abs(frame - avg_color)
    mask = np.all(diff > tol, axis=-1)
    return mask

# Define the function to detect the balls
def detect_balls(frame):
    params = cv2.SimpleBlobDetector_Params()
    params.filterByArea = True
    params.minArea = 100
    params.filterByCircularity = True
    params.minCircularity = 0.7
    detector = cv2.SimpleBlobDetector_create(params)
    keypoints = detector.detect(frame)
    return keypoints

# Define the function to track the balls
def track_balls(keypoints, balls):
    for keypoint in keypoints:
        x, y = keypoint.pt
        for ball_id, (positions, updated) in balls.items():
            if np.abs(positions[-1][0] - x) <= 10 and np.abs(positions[-1][1] - y) <= 10:
                positions.append((x, y))
                balls[ball_id] = (positions, True)
                break
        else:
            balls[len(balls) + 1] = ([(x, y)], True)
    for ball_id, (positions, updated) in balls.items():
        if not updated:
            balls[ball_id] = (positions, False)
    return balls

# Open the video file and process each frame
cap = cv2.VideoCapture('snooker2.mp4')
balls = {}
while cap.isOpened():
    ret, frame = cap.read()
    if not ret:
        break
    mask = filter_background(frame, tol=50)
    frame = cv2.bitwise_and(frame, frame, mask=mask.astype(np.uint8))
    keypoints = detect_balls(frame)
    balls = track_balls(keypoints, balls)
cap.release()

# Open the video file and process each frame
cap = cv2.VideoCapture('snooker2.mp4')
balls = {}
while cap.isOpened():
    ret, frame = cap.read()
    if not ret:
        break
    mask = filter_background(frame, tol=50)
    frame = cv2.bitwise_and(frame, frame, mask=mask.astype(np.uint8))
    keypoints = detect_balls(frame)
    balls = track_balls(keypoints, balls)

    # Visualization
    for keypoint in keypoints:
        x, y = map(int, keypoint.pt)
        cv2.circle(frame, (x, y), int(keypoint.size), (0, 255, 0), 2)
    for ball_id, (positions, _) in balls.items():
        if positions:
            x, y = map(int, positions[-1])
            cv2.putText(frame, str(ball_id), (x, y), cv2.FONT_HERSHEY_SIMPLEX, 1, (0, 0, 255), 2)

    cv2.imshow('Frame', frame)
    if cv2.waitKey(1) & 0xFF == ord('q'):
        break

cap.release()
cv2.destroyAllWindows()