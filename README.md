## I. 명세 파악

### 1. 개요

본 과제는 **Mandatory Access Control (MAC)** 중 하나인 **Bell-LaPadula Model**을 구현하는 것이 목적입니다.  
구체적으로는 `Read Down`, `Write Up` 정책을 적용하여 **mac**이라는 커맨드라인 툴을 만들고, 이를 리눅스의 **SetUID/SetGID** 기능과 함께 사용하여 **보안 등급에 따른 접근 제어를 실현**합니다.

---

### 2. 요구 사항

#### A. `mac` 실행 파일의 권한 설정

- `mac` 프로그램은 **root user** 및 **root group** 소유로 설정
- 퍼미션은 `6755`로 설정
  - 이는 실행 시, 프로그램이 root 권한으로 실행됨을 의미

#### B. 객체: 파일

- 사전에 생성된 보안 등급별 4개의 문서가 존재함:

| 파일명              | 보안 등급    |
| ------------------- | ------------ |
| `top_secret.data`   | TOP_SECRET   |
| `secret.data`       | SECRET       |
| `confidential.data` | CONFIDENTIAL |
| `unclassified.data` | UNCLASSIFIED |

- 각 파일의 속성:
  - 소유자: `root`, 그룹: `root`
  - 퍼미션: `0640`
  - 파일의 소유자 및 퍼미션은 유지되어야 함

#### C. 객체: 사용자

- **비-root 사용자**는 MAC 정책이 적용됨
- 사용자 등급은 `mac.policy` 파일에 정의됨
  - 파일 포맷: `<user_name>:<security_level>`
  - 소유자: `root`, 퍼미션: `0640`

#### D. 접근 제어 도구: `mac`

- 사용자는 직접 파일을 여는 것이 아니라 `./mac`을 통해 간접 접근
- 직접 접근은 DAC에 의해 제한되고, `mac`은 SetUID로 동작하여 root 권한으로 실행됨

#### E. Root 권한 해제

- `mac` 실행 중 root 권한이 필요하지 않게 되면 반드시 **euid/egid를 변경**하여 root 권한을 해제할 것

#### F. 로그 기록

- 사용자 이름 기반 로그 파일 `<username>.log`를 생성
  - 존재하지 않으면 자동 생성되며, 해당 사용자 소유, 퍼미션은 `0640`
- 로그에는 **명령어 인자**만 기록 (파일의 실제 내용은 기록하지 않음)

#### G. 명령어 인터페이스

모든 인자는 `[a-zA-Z0-9_\-\.]`로 구성되고, 대소문자를 구분함

##### 1) `read`

```
./mac read <file_name>
```

- 조건:
  - 사용자가 `mac.policy`에 등록되어 있어야 함
  - Read Down Policy에 따라 접근 가능해야 함
- 동작:
  - 접근 허용 시: 파일 내용 + 개행 출력
  - 접근 거부 시: `"ACCESS DENIED"`

##### 2) `write`

```
./mac write <file_name> <data>
```

- 조건:
  - 사용자가 `mac.policy`에 등록되어 있어야 함
  - Write Up Policy에 따라 접근 가능해야 함
- 동작:
  - 접근 허용 시: 아무 메시지도 출력하지 않음
  - 접근 거부 시: `"ACCESS DENIED"`

---

## II. 설계

### 1. 구조 설계

#### A. 프로젝트 명명 규칙

- **폴더**
  - 소문자 + 복수형 (기능 그룹 중심): `utils/`, `policies/`, `handlers/`, `controllers/`, `macros/`, `enums/`
- **헤더 파일**
  - 소문자 + 단수형 (객체 중심): `user.h`, `file.h`, `string.h`

#### B. 폴더 구조

```
.
├── controllers/    # 고수준 기능 제어
├── enums/          # enum 타입 정의
├── handlers/       # 핵심 기능 처리
├── macros/         # 매크로 상수 정의
├── policies/       # 보안 정책 정의
├── utils/          # 유틸리티 함수
└── mac.c           # 프로그램 진입점
```

---

### 2. 구현

#### A. `read`

1. `argv[1]`이 `"read"`일 경우 → `handlers/file.c`의 `file_read` 호출
2. `file_read` 동작:

- 사용자와 파일의 보안 등급을 확인 (`mac.policy`)
- **Read-Down Policy** 확인:
  - 사용자의 등급 ≥ 파일의 등급일 때 접근 허용
- 접근 허용 시: 파일을 읽어 출력
- 접근 후: root 권한 해제
- 그 후 사용자 로그 `<username>.log`에 기록
- 파일 열기 실패 → `"ACCESS DENIED"` 출력

#### B. `write`

1. `argv[1]`이 `"write"`일 경우 → `handlers/file.c`의 `file_write` 호출
2. `file_write` 동작:

- 사용자와 파일의 보안 등급을 확인 (`mac.policy`)
- **Write-Up Policy** 확인:
<<<<<<< HEAD
  - 사용자의 등급 ≤ 파일의 등급일 때 접근 허용
- 접근 허용 시: 파일에 `data` 작성
- 접근 후: root 권한 해제
- 사용자 로그에 기록
- 파일 열기 실패 → `"ACCESS DENIED"` 출력

## I. 명세 파악

### 1. 개요

본 과제는 **Mandatory Access Control (MAC)** 중 하나인 **Bell-LaPadula Model**을 구현하는 것이 목적입니다.  
구체적으로는 `Read Down`, `Write Up` 정책을 적용하여 **mac**이라는 커맨드라인 툴을 만들고, 이를 리눅스의 **SetUID/SetGID** 기능과 함께 사용하여 **보안 등급에 따른 접근 제어를 실현**합니다.

---

### 2. 요구 사항

#### A. `mac` 실행 파일의 권한 설정

- `mac` 프로그램은 **root user** 및 **root group** 소유로 설정
- 퍼미션은 `6755`로 설정
  - 이는 실행 시, 프로그램이 root 권한으로 실행됨을 의미

#### B. 객체: 파일

- 사전에 생성된 보안 등급별 4개의 문서가 존재함:

| 파일명              | 보안 등급    |
| ------------------- | ------------ |
| `top_secret.data`   | TOP_SECRET   |
| `secret.data`       | SECRET       |
| `confidential.data` | CONFIDENTIAL |
| `unclassified.data` | UNCLASSIFIED |

- 각 파일의 속성:
  - 소유자: `root`, 그룹: `root`
  - 퍼미션: `0640`
  - 파일의 소유자 및 퍼미션은 유지되어야 함

#### C. 객체: 사용자

- **비-root 사용자**는 MAC 정책이 적용됨
- 사용자 등급은 `mac.policy` 파일에 정의됨
  - 파일 포맷: `<user_name>:<security_level>`
  - 소유자: `root`, 퍼미션: `0640`

#### D. 접근 제어 도구: `mac`

- 사용자는 직접 파일을 여는 것이 아니라 `./mac`을 통해 간접 접근
- 직접 접근은 DAC에 의해 제한되고, `mac`은 SetUID로 동작하여 root 권한으로 실행됨

#### E. Root 권한 해제

- `mac` 실행 중 root 권한이 필요하지 않게 되면 반드시 **euid/egid를 변경**하여 root 권한을 해제할 것

#### F. 로그 기록

- 사용자 이름 기반 로그 파일 `<username>.log`를 생성
  - 존재하지 않으면 자동 생성되며, 해당 사용자 소유, 퍼미션은 `0640`
- 로그에는 **명령어 인자**만 기록 (파일의 실제 내용은 기록하지 않음)

#### G. 명령어 인터페이스

모든 인자는 `[a-zA-Z0-9_\-\.]`로 구성되고, 대소문자를 구분함

##### 1) `read`

```
./mac read <file_name>
```

- 조건:
  - 사용자가 `mac.policy`에 등록되어 있어야 함
  - Read Down Policy에 따라 접근 가능해야 함
- 동작:
  - 접근 허용 시: 파일 내용 + 개행 출력
  - 접근 거부 시: `"ACCESS DENIED"`

##### 2) `write`

```
./mac write <file_name> <data>
```

- 조건:
  - 사용자가 `mac.policy`에 등록되어 있어야 함
  - Write Up Policy에 따라 접근 가능해야 함
- 동작:
  - 접근 허용 시: 아무 메시지도 출력하지 않음
  - 접근 거부 시: `"ACCESS DENIED"`

---

## II. 설계

### 1. 구조 설계

#### A. 프로젝트 명명 규칙

- **폴더**
  - 소문자 + 복수형 (기능 그룹 중심): `utils/`, `policies/`, `handlers/`, `controllers/`, `macros/`, `enums/`
- **헤더 파일**
  - 소문자 + 단수형 (객체 중심): `user.h`, `file.h`, `string.h`

#### B. 폴더 구조

```
.
├── controllers/    # 고수준 기능 제어
├── enums/          # enum 타입 정의
├── handlers/       # 핵심 기능 처리
├── macros/         # 매크로 상수 정의
├── policies/       # 보안 정책 정의
├── utils/          # 유틸리티 함수
└── mac.c           # 프로그램 진입점
```

---

### 2. 구현

#### A. `read`

1. `argv[1]`이 `"read"`일 경우 → `handlers/file.c`의 `file_read` 호출
2. `file_read` 동작:

- 사용자와 파일의 보안 등급을 확인 (`mac.policy`)
- **Read-Down Policy** 확인:
  - 사용자의 등급 ≥ 파일의 등급일 때 접근 허용
- 접근 허용 시: 파일을 읽어 출력
- 접근 후: root 권한 해제
- 그 후 사용자 로그 `<username>.log`에 기록
- 파일 열기 실패 → `"ACCESS DENIED"` 출력

#### B. `write`

1. `argv[1]`이 `"write"`일 경우 → `handlers/file.c`의 `file_write` 호출
2. `file_write` 동작:

- 사용자와 파일의 보안 등급을 확인 (`mac.policy`)
- **Write-Up Policy** 확인:
=======
>>>>>>> 439edce (Fix formatting in README.md for clarity and consistency)
  - 사용자의 등급 ≤ 파일의 등급일 때 접근 허용
- 접근 허용 시: 파일에 `data` 작성
- 접근 후: root 권한 해제
- 사용자 로그에 기록
- 파일 열기 실패 → `"ACCESS DENIED"` 출력
