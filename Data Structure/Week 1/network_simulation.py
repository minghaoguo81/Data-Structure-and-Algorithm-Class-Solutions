from collections import deque


def processPacket(packets, bufsize):
    buffer = deque(maxlen=bufsize)

    start_times = [None] * len(packets)
    for i, (arrival, duration) in enumerate(packets):
        while buffer and buffer[0] <= arrival:
            buffer.popleft()

        if len(buffer) >= bufsize:
            start_times[i] = -1
        else:
            start_times[i] = max(arrival, buffer[-1] if buffer else 0)
            buffer.append(start_times[i] + duration)
    return start_times


if __name__ == '__main__':
    s, n = list(map(int, input().split()))
    packets = []
    for i in range(n):
        packets.append(list(map(int, input().split())))
    times = processPacket(packets, s)
    for time in times:
        print(time)