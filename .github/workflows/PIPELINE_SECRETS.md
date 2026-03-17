# Pipeline Secrets & Variables

Everything you need to configure before the release pipeline can run end-to-end.
All items under **Secrets** go in **Settings → Secrets and variables → Actions → Secrets**.
All items under **Variables** go in **Settings → Secrets and variables → Actions → Variables**.

---

## Secrets

### Windows Code Signing

| Secret | Description |
|---|---|
| `WINDOWS_CERTIFICATE` | Base64-encoded `.pfx` certificate file. |
| `WINDOWS_CERTIFICATE_PWD` | Password that protects the `.pfx`. |

**How to generate**

1. Obtain a code-signing certificate from a CA (e.g. DigiCert, Sectigo) as a `.pfx` file.
2. Base64-encode it:
   ```sh
   base64 -w 0 certificate.pfx
   ```
3. Paste the output as `WINDOWS_CERTIFICATE` and the certificate password as `WINDOWS_CERTIFICATE_PWD`.

---

### macOS Code Signing & Notarization

| Secret | Description |
|---|---|
| `MACOS_CERTIFICATE` | Base64-encoded Developer ID Application `.p12` certificate. |
| `MACOS_CERTIFICATE_PWD` | Password that protects the `.p12`. |
| `MACOS_KEYCHAIN_PWD` | Any random string — used to create a temporary CI keychain. |
| `MACOS_DEVELOPER_NAME` | Your name exactly as registered with Apple (e.g. `Jane Smith`). |
| `MACOS_NOTARIZATION_TEAM_ID` | Your 10-character Apple Developer Team ID (e.g. `AB12CD34EF`). |
| `MACOS_NOTARIZATION_APPLE_ID` | The Apple ID email associated with your developer account. |
| `MACOS_NOTARIZATION_PWD` | An app-specific password for `notarytool` (not your Apple ID password). |

**How to generate**

1. In **Xcode → Settings → Accounts**, download your *Developer ID Application* certificate, then export it as a `.p12` from Keychain Access.
2. Base64-encode it:
   ```sh
   base64 -w 0 certificate.p12
   ```
3. Find your Team ID at [developer.apple.com/account](https://developer.apple.com/account) under **Membership**.
4. Generate an app-specific password at [appleid.apple.com](https://appleid.apple.com) under **Sign-In and Security → App-Specific Passwords**.

---

### Linux GPG Signing

| Secret | Description |
|---|---|
| `LINUX_GPG_PRIVATE_KEY` | Base64-encoded armored GPG private key. |
| `LINUX_GPG_KEY_ID` | Key ID or email used to sign (e.g. `releases@yourgame.com`). |

**How to generate**

1. Create (or select) a GPG key:
   ```sh
   gpg --full-generate-key
   ```
2. Export and base64-encode the private key:
   ```sh
   gpg --export-secret-keys -a YOUR_KEY_ID | base64 -w 0
   ```
3. Paste the output as `LINUX_GPG_PRIVATE_KEY`.
4. Set `LINUX_GPG_KEY_ID` to the key ID or the email address you chose.

**Verifying a signed binary**

Users can verify the `.asc` sidecar shipped alongside each binary:
```sh
gpg --verify minesweeper-c.asc minesweeper-c
```

---

### Steam

| Secret | Description |
|---|---|
| `STEAM_USERNAME` | Username of a dedicated Steamworks build account. |
| `STEAM_CONFIG_VDF` | Base64-encoded `config.vdf` from a logged-in SteamCMD session. |

**How to generate `STEAM_CONFIG_VDF`**

1. Install SteamCMD and log in once interactively (handles Steam Guard):
   ```sh
   steamcmd +login YOUR_BUILD_ACCOUNT
   ```
2. After login succeeds, encode the resulting config file:
   ```sh
   base64 -w 0 ~/Steam/config/config.vdf
   ```
3. Paste the output as `STEAM_CONFIG_VDF`.

> **Note:** Use a dedicated build account, not your personal Steam account. The session in `config.vdf` will expire if Steam Guard re-challenges — re-run the login step and update the secret when that happens.

---

### GOG

| Secret | Description |
|---|---|
| `GOG_CLIENT_ID` | Client ID from the GOG Galaxy pipeline credentials page. |
| `GOG_CLIENT_SECRET` | Client secret paired with the above. |

**Where to find them**

In the [GOG Developer Portal](https://devportal.gog.com), navigate to **Games → Your Game → Pipeline → Credentials**.

---

### itch.io

| Secret | Description |
|---|---|
| `BUTLER_CREDENTIALS` | butler API key for your itch.io account. |

**How to generate**

Generate a key at [itch.io/user/settings/api-keys](https://itch.io/user/settings/api-keys).

---

## Variables

Variables are **not** secret — they are visible in workflow logs.
Add them under **Settings → Secrets and variables → Actions → Variables**.

| Variable | Description | Example |
|---|---|---|
| `STEAM_APP_ID` | Your Steam App ID from Steamworks. | `1234560` |
| `GOG_GAME_ID` | Your GOG product ID from the Developer Portal. | `1234567890` |
| `ITCH_USER` | Your itch.io username. | `janeDev` |
| `ITCH_GAME` | Your itch.io game slug (from the game URL). | `minesweeper-c` |
