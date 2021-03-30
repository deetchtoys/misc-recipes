local cjson = require('cjson.safe')
wrk.method = "POST"
wrk.body = cjson.encode({
  recordId = "wangdiqi",
  requestType = "audio",
  serviceType = "dds",
  ruleName = "DEFAULT",
  targetKey = "1-testdevice"})
wrk.headers["Content-Type"] = "application/json"

local threads = {}

function setup(thread)
    table.insert(threads, thread)
end

function init()
    counter = 1
end

function request()
    return wrk.request()
end


function response(status, headers, body)
    -- print(status)
    -- print(headers)
    print(body)
    counter = counter + 1
end

function done(summary, latency, requests)
    io.write("------------------------------\n")
    for _, p in pairs({ 50, 60, 90, 95, 99, 99.999 }) do
        n = latency:percentile(p)
        io.write(string.format("%g%%, %d ms\n", p, n/1000.0))
    end
end
