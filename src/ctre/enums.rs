pub enum FeedbackSensorSource {
    RotorSensor = 0,
    RemoteCANcoder = 1,
    RemotePigeon2Yaw = 2,
    RemotePigeon2Pitch = 3,
    RemotePigeon2Roll = 4,
    FusedCANcoder = 5,
    SyncCANcoder = 6,
    RemoteCANdiPWM1 = 9,
    RemoteCANdiPWM2 = 10,
    RemoteCANdiQuadrature = 11,
    FusedCANdiPWM1 = 12,
    FusedCANdiPWM2 = 13,
    FusedCANdiQuadrature = 14,
    SyncCANdiPWM1 = 15,
    SyncCANdiPWM2 = 16,
}

pub enum Direction {
    CounterClockwise = 0,
    Clockwise = 1,
}

pub enum NeutralMode {
    Coast = 0,
    Brake = 1,
}
