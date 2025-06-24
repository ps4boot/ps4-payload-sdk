#!/bin/sh
set -e

echo "🎮 Running PS4 Payload SDK Action!"

echo "🏃 Executing command \"$@\""
exec "$@"
echo "💯 Done executing command!"
