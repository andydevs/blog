require "rack/jekyll"

run Rack::Jekyll.new show_drafts: true