# AGENTS.md

## Workflow

- Setiap kali selesai menulis/mengubah code, langsung commit dan push ke GitHub (branch `main`). Jangan tunggu diminta.
- Commit style: Conventional Commits (`feat:`, `fix:`, `chore:`).
- Jangan commit secrets (`.env`, `.env.local`).

## Coding Standards

- **STRICT RULE**: Code harus murni tanpa deskripsi apapun. Developer manusia tidak menggunakan deskripsi atau narasi seperti "Here is the code".
- DILARANG keras menyertakan komentar panjang, komentar markdown, atau narasi AI (seperti penjelasan apa yang diubah). Hanya hasilkan code yang clean.
- Hilangkan marker yang membuat code terlihat seperti buatan AI.